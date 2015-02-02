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
int N = 0;	/**< numero di nodi (posizioni dei fori) */
int A = 0;	/**< numero degli archi (tragitti tra i fori) */

char nameN[N] = NULL;		/**< nomi dei nodi */
char nameA[A] = NULL; 		/**< nomi degli archi */

double C[A] = NULL;			/**< costi di cammino (spostamento tra fori) */
			
const int NAME_SIZE = 512;
char name[NAME_SIZE];
	
/**
* setup problema
*/
void setupLP(CEnv env, Prob lp, int & numVars)
{
	/**
	* add x vars
	* variabili intere che indicano le unità di flusso trasportate 
	* dal nodo i al nodo j
	*/
	const int x_init = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i != j)
			{
				char xtype = 'I';
				double obj = 0.0;
				double lb = 0.0;
				double ub = CPX_INFBOUND;
				snprintf(name, NAME_SIZE, "x_%c_%c", nameN[i], nameN[j]);
				char* xname = (char*)(&name[0]);
				CHECKED_CPX_CALL( CPXnewcols, env, lp, 1, &obj, &lb, &ub, 
					&xtype, &xname );
			}
		}
	}


	/**
	* add y vars
	* variabili binarie che indicano l'utilizzo di un arco
	*/
	const int y_init = CPXgetnumcols(env, lp); /**< numero di variabili del problema */

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i != j)
			{
				char ytype = 'B';
				double lb = 0.0;
				double ub = 1.0;
				snprintf(name, NAME_SIZE, "y_%c_%c", nameN[i], nameN[j]);
				char* yname = (char*)(&name[0]);
				CHECKED_CPX_CALL( CPXnewcols, env, lp, 1, &C[i*N+j], &lb, &ub, 
					&ytype, &yname );
			}
		}
	}

	numVars = CPXgetnumcols(env, lp);	/**< numero di variabili del problema */

	/**
	* vincolo di flusso sul nodo di partenza
	*/
	{
		char sense = 'E';
		int rmatbeg = 0;
		std::vector<int> rmatind;
		std::vector<double> rmatval;
		for (int j = 0; j < N - 1; j++)
		{
			rmatind.push_back(j);
			rmatval.push_back(1.0);
		}

		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, rmatind.size(), 
			&N, sense, &rmatbeg, &rmatind[0], &rmatval[0], NULL, NULL)
	}

	/**
	* vincolo di bilanciamento del flusso su tutti i nodi escluso quello di partenza
	*/
	for (int k = 1; k < N; ++k)
	{
		char sense = 'E';
		int rmatbeg = 0;
		std::vector<int> rmatind;
		std::vector<double> rmatval;

		// flusso entrante nel nodo k
		for (int i = 0; i < N; ++i)
		{
			if(i != k)
			{
				rmatind.push_back(i*(N - 1) + k);
				rmatval.push_back(1.0);
			}
		}

		// flusso uscente dal nodo k
		for (int j = k + 1; j < N; ++j)
		{
			rmatind.push_back(j);
			rmatval.push_back(-1.0);
		}

		double rhs = 1;

		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, rmatind.size(),
			&rhs, sense, &rmatbeg, &rmatind[0], &rmatval[0], NULL, NULL)
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
		if (n != numVars) { 
			throw std::runtime_error(std::string(__FILE__) + ":" 
				+ STRINGIZE(__LINE__) + ": " 
				+ "different number of variables");
		}
	  	std::vector<double> varVals;
	  	varVals.resize(n);
  		CHECKED_CPX_CALL( CPXgetx, env, lp, &varVals[0], 0, n - 1 );
		/// status = CPXgetx (env, lp, x, 0, CPXgetnumcols(env, lp)-1);
	  	for ( int i = 0 ; i < n ; ++i ) {
	  	  	std::cout << "var in position " << i << " : " 
	  	  		<< varVals[i] << std::endl;
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
