#pragma once

// ----------------------------------
// --- Create output tables       ---
// ----------------------------------


void process_bestSols      ();
void process_bestSol       (int instanceType, ofstream &file);

void process_allSolTime        ();
void process_allSettings_short ();
void process_allSettings_long  ();

void process_compareBoth ();

void process_output_files (int instanceType);
void process_output_files_for_cuts ();

tuple<size_t, size_t> hash_and_set_globals (size_t const instType, size_t const idx_inst);

void process_output_files (int instanceType);
void process_roots (string);
void process_all_roots ();
