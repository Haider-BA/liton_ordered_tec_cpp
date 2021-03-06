# include <iostream>
# include <stdlib.h>
using namespace std;
# include "../../scr/ordered_tec.h"
using namespace liton_ot;

# define DATATYPE double
int main(int argc, char **argv)
{
	DATATYPE *x, *y, *z, *w;
	size_t NI = 20, NJ = 40;
	try
	{
		x = new DATATYPE[NI*NJ];
		y = new DATATYPE[NI*NJ];
		z = new DATATYPE[NI*NJ];
		w = new DATATYPE[NI*NJ];
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
			z[i + j*NI] = 1 + i / 2 + j;
			w[i + j*NI] = i + j;
		}
	}

	TEC_FILE tecfile("test_10", ".", "test_10");
	tecfile.Variables.push_back("x");
	tecfile.Variables.push_back("y");
	tecfile.Variables.push_back("z");
	tecfile.add_auxiliary_data("Auxiliary1", "Auxiliary_test_1_ds");
	tecfile.add_auxiliary_data("Auxiliary2", 3.14);

	tecfile.Zones.push_back(TEC_ZONE("A"));
	tecfile.Zones[0].Max[0] = NI;
	tecfile.Zones[0].Max[1] = NJ;
	tecfile.Zones[0].Data.push_back(TEC_DATA(x));
	tecfile.Zones[0].Data.push_back(TEC_DATA(y));
	tecfile.Zones[0].Data.push_back(TEC_DATA(z));
	tecfile.Zones[0].add_auxiliary_data("Auxiliary1", "Auxiliary_test_1");
	tecfile.Zones[0].add_auxiliary_data("Auxiliary2", 3.14);

	tecfile.Zones.push_back(tecfile.Zones[0]);
	tecfile.Zones[1].Begin[0] = 5;
	tecfile.Zones[1].End[0] = 5;
	tecfile.Zones[1].Begin[1] = 1;
	tecfile.Zones[1].End[1] = 1;
	tecfile.Zones[1].Skip[0] = 2;
	tecfile.Zones[1].Skip[1] = 4;
	tecfile.Zones[1].ZoneName = "B";
	tecfile.Zones[1].Data[2] = TEC_DATA(w);
	tecfile.Zones[1].Auxiliary.clear();
	tecfile.Zones[1].add_auxiliary_data("Auxiliary3", "Auxiliary_test_1_2");
	tecfile.Zones[1].add_auxiliary_data("Auxiliary4", 3.1415);

	cout << "FileName " << tecfile.last_log.FileName << endl;
	cout << "FilePath " << tecfile.last_log.FilePath << endl;
	cout << "FileType " << tecfile.last_log.FileType << endl;
	cout << "Title " << tecfile.last_log.Title << endl;
	cout << "Error " << tecfile.last_log.Error << endl;
	cout << "Size " << tecfile.last_log.Size << endl;
	cout << "Time_Begin " << tecfile.last_log.Time_Begin << endl;
	cout << "Time_End " << tecfile.last_log.Time_End << endl;
	cout << "UsingTime " << tecfile.last_log.UsingTime << endl;
	cout << "Variables.size " << tecfile.last_log.Variables.size() << endl;
	cout << "Auxiliary.size " << tecfile.last_log.Auxiliary.size() << endl;
	cout << "Echo_Text.size " << tecfile.last_log.Echo_Text.size() << endl;
	cout << "Json_Text.size " << tecfile.last_log.Json_Text.size() << endl;
	cout << "Xml_Text.size " << tecfile.last_log.Xml_Text.size() << endl;
	cout << "Zones.size " << tecfile.last_log.Zones.size() << endl;

	try
	{
		tecfile.set_echo_mode("full", "full");
		tecfile.write_plt();
		tecfile.last_log.write_echo();
		tecfile.last_log.write_json();
		tecfile.last_log.write_xml();
		tecfile.last_log.Zones[0].write_echo();
		tecfile.last_log.Zones[0].write_json();
		tecfile.last_log.Zones[0].write_xml();
		cout << tecfile.last_log.Zones[0].Dim << endl;
		cout << tecfile.last_log.Zones[0].Real_Dim << endl;
	}
	catch (runtime_error err)
	{
		cerr << "runtime_error: " << err.what() << endl;
	}

	delete[] x;
	delete[] y;
	delete[] z;
	delete[] w;
	return 0;
}