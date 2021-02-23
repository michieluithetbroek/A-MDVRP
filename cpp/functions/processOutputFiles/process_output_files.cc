#include "./../../main.ih"

/*
 * instancetype = 0, 3, 6, or 9 
 * 
 */

void process_output_files (int instanceType)
{
  int constexpr nRep   = 3;
  string const setting = "250_200_200";
  string const thread  = "_nThreads-5";
  string const sleep   = "_sleep-60";
  string const repIdx  = "_repIdx-1";
   
  for (string alg: {"base", "base_plusBoth"})
  {
    cout << alg << "-" << instanceType << " ------------------------------- \n";
    stringstream tmp;
    tmp << fixed;
        
    int instance_ctr = 0;
    
    set_global_enums(instanceType);
        
    auto const characs = get_characs(instanceType);

    for (auto el: characs)
    {
      for (int rep = 0; rep != nRep; ++rep)
      {
        string name ("\\_" + to_string(el[1]) + "\\_" +to_string(el[0]) + "\\_" + to_string(rep) );
        
        tmp << setw(18) << name << " & ";
        
        bool payAttention = false;
        
        for (int idx = 0; idx < 3; ++idx)
        {
          set_global_enums(instanceType + idx);
          
          string const fileName = "./../analysis_new/tuning/"
                                  + getInstanceName() + "/"
                                  + alg + "/"
                                  + setting + "/n"
                                  + to_string(el[1]) + "m"
                                  + to_string(el[0]) + "_" 
                                  + to_string(rep) 
                                  + thread 
                                  + sleep 
                                  + repIdx; 
                                  
          ResultSingleFile file(fileName);
          //cout << fileName;
          
          if (not file.fileFound)
            throw string("Result file not found (process_output_files)");
          
          tmp << setprecision(0) 
              << setw(6) << round(file.LB) << " & ";
              
          if (file.UB != 0)
          {
            tmp << setw(6) << file.UB << " & ";
          
            if (file.gap <= 0.00001)
              tmp << setprecision(2) << setw(15) << "\\textbf{0.00}" << " & ";
            else
              tmp << setprecision(2) << setw(15) << file.gap << " & ";
          }
          else
            tmp << setw(6) << "-" << " & "
                << setw(15) << "-" << " & ";
          
          int time_cutOff = file.time;
          
          if (time_cutOff > 18000)
          {
            cout << setw(10) << file.time << endl;
            time_cutOff = 18000;
          }
          
          tmp << setprecision(0) 
              << setw(6) << file.nodes / 1000 << " & "
              << setw(6) << time_cutOff; 
          
          if (idx < 2)
            tmp << " & ";
          
          else
            tmp << " \\\\";
                    
          //cout << " " << file.gap << endl;
          //increase instance ctr
          ++instance_ctr;
                    
          
          if (file.gap > 0.00 and time_cutOff < 15000 and file.nodes < 20000)
            payAttention = true;
          
          if (file.LB < 5)
            payAttention = true;
      
          
        }
        
        if (payAttention)
          tmp << " % <--- check this line";
          
        tmp << '\n';
      }
    }
    
    
    // Print the table
   cout << tmp.str() << endl << endl;
  }        
  
}
