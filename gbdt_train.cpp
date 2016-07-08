#include "gradient_boosting.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void my_memset(double* x, int count, int value)
{
	for(int i = 0; i < count; i++)
	{
		x[i] = value;
	}
}
 
 bool has_colon(string item)
 {
	for(int i = 0; i < (int)item.size(); i++)
  	{
		if(item[i] == ':')
		return true;
  	}
 
  	return false;
 }



//
//	x[][] :  {sample x feature} matrix
//	y[]   :	 target vector
//
int read_train_file( double*& x, double*& y, gbdt_info_t infbox)
{
	double value;

	x = (double*) malloc (infbox.data_num * infbox.fea_num * sizeof(double));
	y = (double*) malloc (infbox.data_num * sizeof(double));

	my_memset(x, infbox.data_num * infbox.fea_num, NO_VALUE);
	my_memset(y, infbox.data_num, NO_VALUE);

	int cnt		= 0;
	int count	= 0;
	int fid;

	ifstream fptrain(infbox.train_filename);
	string* items = new string[infbox.fea_num+5]; 
	string line;
	int x_read;

	while (getline(fptrain, line) != NULL) {
		count = splitline(line, items, infbox.fea_num+5, ' '); 
		sscanf(items[0].c_str(),"%lf",&value);

		//the first column is y
		y[cnt] = value; 

		for(int i = 1; i < count; i++) {
			if(has_colon(items[i]))	{
				//featureid1:value1 featureid2:value2 ... density matrix x
				x_read = sscanf(items[i].c_str(),"%d:%lf", &fid, &value); 
				x[cnt*infbox.fea_num + fid] = value;
			}
		}
		cnt ++;
		if (cnt >= infbox.data_num)	{ 
			break;
		}
	}
 
	delete[] items;
	fptrain.close();
	return 0;
}




int main(int argc, char* argv[])
{
	double *x = NULL;
	double *y = NULL;

	gbdt_info_t infbox;
	char log_message[BUFFER_LENGTH];

	int res = read_conf_file(infbox, argc, argv);

	snprintf(log_message, BUFFER_LENGTH, "Reading training data from: %s ...", infbox.train_filename);
	
	// load 训练数据
	read_train_file(x, y, infbox); 

	// 开始模型训练
	gbdt_model_t* gbdt_model = gbdt_regression_train(x, y, infbox);

	gbdt_save_model(gbdt_model, infbox.model_filename); 

	free_model(gbdt_model);
	
	return 0;
}
