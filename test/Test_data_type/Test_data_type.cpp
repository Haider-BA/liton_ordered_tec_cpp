# include <iostream>
# include <cmath>
using namespace std;
# include "../../scr/ordered_tec.h"
using namespace liton_ot;

template<typename T>
void set_data(T *data, TEC_FILE &tecfile)
{
	int NI = tecfile.Zones[0].Max[0];
	int NJ = tecfile.Zones[0].Max[1];
	for (int j = 0; j != NJ; ++j)
	{
		for (int i = 0; i != NI; ++i)
		{
			data[i + j*NI] = static_cast<T>(5 * (sin(static_cast<double>(j) / 500) - cos(static_cast<double>(i) / 500)));
		}
	}
	tecfile.Zones.push_back(tecfile.Zones[0]);
	try
	{
		(tecfile.Zones.end() - 1)->Data.push_back(TEC_DATA(data));
	}
	catch (runtime_error err)
	{
		cerr << "runtime_error: " << err.what() << endl;
		tecfile.Zones.pop_back();
		return;
	}
}

int main(int argc, char **argv)
{
	double *x, *y;
	signed char *p_byte;
	short int *p_shortint;
	int *p_int;
	float *p_float;
	double *p_double;

	size_t NI = 1000, NJ = 2000;
	try
	{
		x = new double[NI*NJ];
		y = new double[NI*NJ];
		p_byte = new signed char[NI*NJ];
		p_shortint = new short int[NI*NJ];
		p_int = new int[NI*NJ];
		p_float = new float[NI*NJ];
		p_double = new double[NI*NJ];
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
		}
	}

	TEC_FILE tecfile("test_09");
	tecfile.Variables.push_back("x");
	tecfile.Variables.push_back("y");
	tecfile.Variables.push_back("z");
	tecfile.Zones.push_back(TEC_ZONE("test_09"));
	tecfile.Zones[0].Max[0] = NI;
	tecfile.Zones[0].Max[1] = NJ;
	tecfile.Zones[0].Data.push_back(TEC_DATA(x));
	tecfile.Zones[0].Data.push_back(TEC_DATA(y));

	cout << "signed char" << endl;
	set_data(p_byte, tecfile);
	cout << "short int" << endl;
	set_data(p_shortint, tecfile);
	cout << "long int" << endl;
	set_data(p_int, tecfile);
	cout << "float" << endl;
	set_data(p_float, tecfile);
	cout << "double" << endl;
	set_data(p_double, tecfile);

	tecfile.Zones.erase(tecfile.Zones.begin());
	tecfile.set_echo_mode("full", "full");

	try
	{
		tecfile.write_plt();
		tecfile.last_log.write_xml();
	}
	catch (runtime_error err)
	{
		cerr << "runtime_error: " << err.what() << endl;
	}

	try
	{
		tecfile.Zones[0].Data.push_back(TEC_DATA(&NI));
	}
	catch (runtime_error err)
	{
		cerr << "runtime_error: " << err.what() << endl;
	}

	delete[] x;
	delete[] y;
	delete[] p_byte;
	delete[] p_shortint;
	delete[] p_int;
	delete[] p_float;
	delete[] p_double;

	return 0;
}