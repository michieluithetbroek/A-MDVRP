#include "./random2.ih"

namespace random2
{
  default_random_engine d_generator(2);
  
  void setSeed(unsigned seed)
  {
    d_generator.seed(seed);
  }
  
  default_random_engine &engine()
  {
    return d_generator;
  }  
  
  vector<size_t> random_indices(size_t min, size_t max)
  {
    
    size_t const size = max - min + 1;
    
//     cout << "min " << min << endl
//          << "max " << max << endl;
//     cout << size << endl;
    
    vector<size_t> indices(size);
    iota(begin(indices), end(indices), min);
    shuffle(begin(indices), end(indices), d_generator);
    
    for (size_t idx = 0; idx < size; ++idx)
    {
      indices[idx] += min;
//       cout << indices[idx] << endl;
    }
    
    cout << "size: " << indices.size() << endl;
    
    return vector<size_t>(begin(indices), begin(indices));
  }
  
  vector<size_t> random_indices(size_t min, size_t max, size_t n)
  {
    size_t const size = max - min + 1;
    
    vector<size_t> indices(size);
    iota(begin(indices), end(indices), min);
    shuffle(begin(indices), end(indices), d_generator);
    
    return vector<size_t>(cbegin(indices), cbegin(indices) + n);
  }  
}