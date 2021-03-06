# include <iostream>
# include <sstream>
# include <fstream>
# include <cmath>
using namespace std;
# include "../../scr/ordered_tec.h"
using namespace liton_ot;

# define DATATYPE double

void write_plt(TEC_FILE & tecfile, ofstream &log)
{
	try
	{
		tecfile.write_plt(false);
		tecfile.last_log.write_echo(log);
		log << "speed: " 
			<< (tecfile.Zones[0].get_real_size()[0]
				*tecfile.Zones[0].get_real_size()[1]
				*tecfile.Zones[0].get_real_size()[2]) / tecfile.last_log.UsingTime 
			<< " N/s"
			<< endl;
	}
	catch (runtime_error err)
	{
		cerr << "runtime_error: " << err.what() << endl;
	}
	cout << "----------------------" << endl;
}

int main(int argc, char **argv)
{
	DATATYPE *x, *y, *z;
	size_t NI = 3000, NJ = 6000;
	try
	{
		x = new DATATYPE[NI*NJ];
		y = new DATATYPE[NI*NJ];
		z = new DATATYPE[NI*NJ];
	}
	catch (...)
	{
		cerr << "runtime_error: out of memery" << endl;
		return 0;
	}
	for (int j = 0; j != NJ; ++j)
	{
		for (int i = 0; i != NI; ++i)
		{
			x[i + j*NI] = j;
			y[i + j*NI] = i;
			z[i + j*NI] = sin(x[i + j*NI] / 1500) - cos(y[i + j*NI] / 3000);
		}
	}

	TEC_FILE tecfile("test_08");
	tecfile.Variables.push_back("x");
	tecfile.Variables.push_back("y");
	tecfile.Variables.push_back("z");
	tecfile.Zones.push_back(TEC_ZONE("test_08"));
	tecfile.Zones[0].Max[0] = NI;
	tecfile.Zones[0].Max[1] = NJ;
	tecfile.Zones[0].Data.push_back(TEC_DATA(x));
	tecfile.Zones[0].Data.push_back(TEC_DATA(y));
	tecfile.Zones[0].Data.push_back(TEC_DATA(z));
	tecfile.set_echo_mode("none", "001111000");

	ofstream log("test_08.txt");

	write_plt(tecfile,log);

	tecfile.Zones[0].Begin[1] = 200;
	tecfile.Zones[0].End[1] = 200;
	write_plt(tecfile, log);

	tecfile.Zones[0].Begin[0] = 100;
	tecfile.Zones[0].End[0] = 100;
	write_plt(tecfile, log);

	tecfile.Zones[0].Skip[1] = 3;
	write_plt(tecfile, log);

	tecfile.Zones[0].Skip[0] = 3;
	write_plt(tecfile, log);

	log.close();

	delete[] x;
	delete[] y;
	delete[] z;
	return 0;
}