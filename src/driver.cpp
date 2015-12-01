/**
 * @file
 * @auther Jessica Li, Jingwen Wang, Hamik Mukelyan
 *
 * This file reads a network description from a JSON file then starts a
 * simulation of the network. It logs data as the simulation progresses then
 * dumps it to to disk so scripts can generate graphs.
 */

// ---------------------------- Includes --------------------------------------

// Standard headers.
#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>

// Custom headers.
#include "simulation.h"

using namespace std;

// --------------------------- Prototypes -------------------------------------

/**
 * Prints a usage statement to stderr.
 * @param progname name of this program.
 */
void print_usage_statement (char *progname);

/**
 * Processes console arguments, returning the input filename and setting flags
 * like the debug one.
 * @param argc number of console arguments
 * @param argv console arguments
 * @return the input filename
 * @post sets the debug flag
 * @warning exits from this process after printing a usage statement if the
 * console arguments don't conform to the usage statement
 */
char *process_console_args(int argc, char **argv);

// ------------------------ Global variables ----------------------------------

/** If true lots of debugging output is shown. */
bool debug = false;

/**
 * If true even more debugging output is shown and the output pauses between
 * events for analysis.
 */
bool detail = false;

/**
 * Output stream to which to write debugging statements. Might be customized
 * to be a file output stream, stderr, or something else.
 */
ostream &debug_os = cout;

// ------------------------------ Main ----------------------------------------

/**
 * Reads a JSON file from disk, populates in-memory collections of hosts,
 * routers, links, and flows, starts a simulation, then logs data.
 */
int main (int argc, char **argv) {

	char *infile = process_console_args(argc, argv);

	// Load hosts, routers, links, and flows from the JSON input file.
	simulation sim(infile);

	// Create a file in which to log data
	string logName = infile;
	
	// .json output file should end up on plot/ directory
	logName = logName.substr(11, 20);	
	logName = "plot" + logName + "_log" + ".json";
	sim.initializeLog(logName);
	cout << "log initialized" << endl;
	// Invoke the simulation loop, which should terminate when all events
	// have been processed.
	// Every time an event is executed, network sim metrics are logged.
	sim.runSimulation();
	cout << "simulation ended" << endl;
	// Close .json format log file 
	sim.closeLog();

	return 0;
}

// ---------------------------- Functions  ------------------------------------

void print_usage_statement (char *progname) {
	cerr << "Usage: " << progname << " <JSON input file> [-d|-dd]" << endl;
	cerr << "  -d to print debugging statements to stdout." << endl;
	cerr << "  -dd to print detailed, pausing debugging statements to stdout."
			<< endl;
}

char *process_console_args(int argc, char **argv) {

	// See print_usage_statement function for expected console arguments.
	if (argc != 2 && argc != 3) {
		print_usage_statement(argv[0]);
		exit (1);
	}

	if (argc == 2) {
		if (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-dd") != 0)
			return argv[1];
		else {
			print_usage_statement(argv[0]);
			exit (1);
		}
	}

	if (argc == 3) {
		if (strcmp(argv[1], "-d") == 0) {
			debug = true;
			return argv[2];
		}
		else if (strcmp(argv[1], "-dd") == 0) {
			debug = true;
			detail = true;
			return argv[2];
		}
		else {
			if (strcmp(argv[2], "-d") == 0)
				debug = true;
			if (strcmp(argv[2], "-dd") == 0) {
				debug = true;
				detail = true;
			}
			return argv[1];
		}
	}

	// Shouldn't get here.
	print_usage_statement(argv[0]);
	exit (1);
}
