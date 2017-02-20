
#include "main.h"
//#include <array>

//#include <cstdlib>
//#include <ctime>

g_program all;
namespace qi = boost::spirit::qi;
int     thething = 0;

int		is_comment(char c)
{
	static int del = 0;
	if ((del == 0 && c == '#') | (del == 1 && c != '\n'))
	{
		del = 1;
		return 1;
	}
	else
	{
		del = 0;
		return 0;
	}
}


std::vector<short> generate_fromsize(int size){
    std::vector<short> ints(size * size, -1);
    std::vector <short > rmat(size * size, -1);

    srand (time(NULL));
    int i = 0;
    while (i < (size * size))
    {
        int test = (rand() % (size * size));
        if (ints[test] == -1) {
            ints[test] = 0;
            (rmat)[i] = test;
        }
        else
            continue;
        i++;
    }
	all.size = size;
    all.finalsnail = snail (all.size, all.size);
    all.final = final();
    return rmat;
}

std::vector<short> parse_fromfile(std::string file)
{
	std::ifstream  in(file);
	std::string oname((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	std::vector<short> ints;
	int				 size;

    oname.erase(remove_if(oname.begin(), oname.end(),&is_comment),oname.end());
	const std::string::iterator F = oname.begin(), l =oname.end();
	qi::phrase_parse(F, l, *qi::short_, qi::space, ints);
		// std::cout << ints.size() << " ushort_ parsed\n";
    if (ints.size() == 0) {
        std::cout<<"Bad file"<<std::endl;
        std::exit(1);
    }
    size = ints[0] * ints[0];
    all.size = ints[0];
    all.finalsnail = snail (all.size, all.size);
    all.final = final();
	if ((ints.size() - 1) != size)
		throw "size";
	ints.erase(ints.begin());
	for (int i = 0; i < size; i++)
	{
		auto it = find (ints.begin(), ints.end(), i);
		if (it == ints.end())
			throw "invalid file";
	}
	for(auto d : ints)
	{
		std::cout  <<d << " ";
	}
	return ints;
}
//-help -d heurestic/manhattan1 hamming2 eucledian3/ string -g greedy/unicost [-f filestring ||  -s size int]
int main(int ac, char **av)
{
	// namespace   po = boost::program_options;
    int         sol;
	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("heuristic,d", boost::program_options::value<std::string>()->required(), "set heuristic manhattan/hamming/tilesout")
		("size,s", boost::program_options::value<int>(), "set the size of the puzzle")
		("greedy,g", "set greedy search")
		("unicost,u", "set unicost search")
		("file,f", boost::program_options::value<std::string>(), "set a input file")
		;
	boost::program_options::variables_map vm;

	try {
        boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);
		boost::program_options::notify(vm);

		if (ac == 1)
			std::cout	<< "use --help to see options" <<std::endl
						<<"USAGE: ./npuzzle [-hguf] -s ARG -d ARG " <<std::endl;
		if (vm.count("help")) {
			std::cout << desc << "\n";
			return 1;
		}
	}
	catch (boost::program_options::error& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
		std::cerr << desc << std::endl;
        return 0;
	}
	try {
        if (vm.count("greedy"))
        {
            all.greedy = true;
        }
        if (vm.count("unicost"))
        {
            all.unicost = true;
        }
        if (vm.count("heuristic"))
        {
            if (!vm["heuristic"].as<std::string>().compare("manhattan"))
                all.heuristic = 1;
            else if (!vm["heuristic"].as<std::string>().compare("hamming"))
                all.heuristic = 2;
            else if (!vm["heuristic"].as<std::string>().compare("tilesout"))
                all.heuristic = 3;
            else{
                std::cout<< desc << std::endl;
                std::cerr   << "ERROR : wrong heuristic" <<std::endl;
                return 0;
            }
        }
		if (!vm.count("size") && !vm.count("file")){
			std::cout<< desc << std::endl;
			std::cerr   << "ERROR : either map size or input_file are mandatory" <<std::endl;
            return 0;
		}
		if (vm.count("file"))
            sol = solvable(parse_fromfile(vm["file"].as<std::string>()), all.size);
        else if (vm.count("size"))
            sol = solvable(generate_fromsize(vm["size"].as<int>()), vm["size"].as<int>());

	}
	catch (const char * e)
	{
		std::cout <<"Error: "<< e <<"\n";
	}
}
