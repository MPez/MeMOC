/**
 * @author 	Marco Pezzutti - 1084411
 * @file 	eserc.lab.01.cpp
 * @brief 	Esercitazione di laboratorio 1
 * @date 	novembre 2014
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include "cpxmacro.h"

using namespace std;

/** 
* error status and messagge buffer
*/
int status;
char errmsg[BUF_SIZE];

/**
* problem data
*/
const int N;	/**< numero di nodi (posizioni dei fori) */
const int A;	/**< numero degli archi (tragitti tra i fori) */

const char nameN[N] = NULL;		/**< nomi dei nodi */
const char nameA[A] = NULL; 	/**< nomi degli archi */

const double C[N*A];			/**< costi di cammino (spostamento tra fori) */
			
const int NAME_SIZE = 512;
char name[NAME_SIZE];
	
/**
* setup problema
*/
void setupLP(CEnv env, Prob lp, int & numVars)
{
	/**
	* add y vars
	* unità di flusso trasportate dal nodo i al nodo j
	*/
	const int y_init = 0;

	std::vector<char> ytype(A, 'B');
	double lb = 0.0;
	double up = CPX_INFBOUND;

	CHECKED_CPX_CALL(CPXnewcols, env, lp, N, &C[0], &lb, &up, &ytype[0], NULL);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < A; j++)
		{
			char ytype = 'B';
			double obj = 0.0;
			double lb = 0.0;
			double ub = CPX_INFBOUND;
			snprintf(name, NAME_SIZE, "h_%c_%c", nameI[i], nameK[k]);
			char* hname = (char*)(&name[0]);
			CHECKED_CPX_CALL( CPXnewcols, env, lp, 1, &obj, &lb, &ub, &htype, &hname );
		}
	}

	
	
	numVars = CPXgetnumcols(env, lp);
	// add finish-time constraints ( y >= h_{i S[i,|K|]} + D_{i S[i,|K|]} )
	for (int i = 0; i < I; i++)
	{
		std::vector<int> idx(2);
		idx[0] = yIdx;
		idx[1] = h_init + i*K + S[i*K + (K-1)]; // sigma(i,last)
		std::vector<double> coef(2);
		coef[0] = 1.0;
		coef[1] = -1.0;
		char sense = 'G';
		int matbeg = 0;
		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &D[i*K + S[i*K + (K-1)]], &sense, &matbeg, &idx[0], &coef[0], 0, 0 );
	}
	// add wake-up constraints ( h_{i S[i,|K|]} >= R_i )
	for (int i = 0; i < I; i++)
	{
		int idx = h_init + i*K + S[i*K + 0];
		double coef = 1.0;
		char sense = 'G';
		int matbeg = 0;
		CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, 1, &D[i*K + S[i*K + 0]], &sense, &matbeg, &idx, &coef, 0, 0 );
	}
	
	// add non-overlapping constraints between consecutive newspapers ( h_{i S[i,l]} >= h_{i S[i,l-1]} + D_{i S[i,l-1]} ) 
	for (int i = 0; i < I; i++)
	{
		for (int l = 1; l < K; l++)
		{
			std::vector<int> idx(2);
			idx[0] = h_init + i*K + S[i*K + l]; 
			idx[1] = h_init + i*K + S[i*K + (l-1)]; 
			std::vector<double> coef(2);
			coef[0] = 1.0;
			coef[1] = -1.0;
			char sense = 'G';
			int matbeg = 0;
			CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &D[i*K + S[i*K + (l-1)]], &sense, &matbeg, &idx[0], &coef[0], 0, 0 );
		}
	}
	// add non-overlapping constraints between persons on the same newspaper 
	int xIdx = x_init;
	for (int k = 0; k < K; k++)
	{
		for (int i = 0; i < I; i++)
		{
			for (int j = i + 1; j < I; j++)
			{
				// 1 ( h_{i k} >= h_{j k]} + D_{j k]} - M x_ijk )
				std::vector<int> idx(3);
				idx[0] = h_init + i*K + k;
				idx[1] = h_init + j*K + k;
				idx[2] = xIdx;
				std::vector<double> coef(3);
				coef[0] = 1.0;
				coef[1] = -1.0;
				coef[2] = M;
				char sense = 'G';
				int matbeg = 0;
				CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &D[j*K + k], &sense, &matbeg, &idx[0], &coef[0], 0, 0 );
				// 2 ( h_{j k} >= h_{i k]} + D_{i k]} - M (1 -x_ijk) )
				idx[0] = h_init + j*K + k;
				idx[1] = h_init + i*K + k;
				idx[2] = xIdx;
				coef[0] = 1.0;
				coef[1] = -1.0;
				coef[2] = -M;
				sense = 'G';
				matbeg = 0;
				double rhs = D[i*k + k] - M;
				CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], 0, 0 );
				
				
				xIdx++; // we have as many constraints as many x variables
					// and the nested loops for constraints adding 
					// follow the same order as the one for x variable adding
			}
		}
	}
	// print (debug)
	CHECKED_CPX_CALL( CPXwriteprob, env, lp, "giornali.lp", 0 );
}

int main (int argc, char const *argv[])
{
	try
	{
		// init
		DECL_ENV( env );
		DECL_PROB( env, lp );
		
		// setup LP
		int numVars;
		setupLP(env, lp, numVars );
		
		// optimize
		CHECKED_CPX_CALL( CPXmipopt, env, lp );
		
		// print objval
		double objval;
		CHECKED_CPX_CALL( CPXgetobjval, env, lp, &objval );
		std::cout << "Objval: " << objval << std::endl;
		
		//print solution (var values)
		int n = CPXgetnumcols(env, lp);
		if (n != numVars) { throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + "different number of variables"); }
	  std::vector<double> varVals;
	  varVals.resize(n);
  	CHECKED_CPX_CALL( CPXgetx, env, lp, &varVals[0], 0, n - 1 );
		/// status = CPXgetx (env, lp, x, 0, CPXgetnumcols(env, lp)-1);
  	for ( int i = 0 ; i < n ; ++i ) {
  	  std::cout << "var in position " << i << " : " << varVals[i] << std::endl;
  	  /// to get variable name, use the RATHER TRICKY "CPXgetcolname"
  	  /// status = CPXgetcolname (env, lp, cur_colname, cur_colnamestore, cur_storespace, &surplus, 0, cur_numcols-1);
  	}
		CHECKED_CPX_CALL( CPXsolwrite, env, lp, "giornali.sol" );
		// free
		CPXfreeprob(env, &lp);
		CPXcloseCPLEX(&env);
	}
	catch(std::exception& e)
	{
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}
