# HPC
## First Three (openmp) (g++ or gcc)
1. g++ -fopenmp dfs.cpp -o dfs_obj_file
2. ./dfs_obj_file

## Last (cuda) (run object files from root on server)
1. ssh {ip_of_gpu_server}
2. nvcc file_name.cu -o file_name_obj_file
3. ./file_name_obj_file
