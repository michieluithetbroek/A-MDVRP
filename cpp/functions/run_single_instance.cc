// #include "../main.ih"
// 
// 
// /*
//  * 
//  * 
//  */
// 
// 
// 
// void run_single_instance (Data const &dat, string const fileName, int cutSetting)
// {
//   // TODO this should be processed by the make_cut_vector function
//   vector<shared_ptr<Cut>> cuts;
//   
//   if (cutSetting == 0)
//     cuts = make_cut_vector_0(dat);
//   
//   else
//     cuts = make_cut_vector_1(dat);
//   
//   thread_modelA t2(thread2, dat, cuts);
//   
//   if (g_useGurobi)
//   {
//     thread_modelC t1(thread1, dat);
//     t1.join(); 
//   }
//   
//   t2.join();
//   
//   print_cut_overview (fileName, dat, cuts);
// }
