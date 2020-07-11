#include <torch/extension.h>
#include <vector>

// CUDA forward declarations
torch::Tensor blocksparse_matmul_transpose_cuda(torch::Tensor dense_a,
								      torch::Tensor row_ends_b,
								      torch::Tensor cols_b,
								      torch::Tensor data_b,
								      int size_rows_b,
								      int size_cols_b,
								      int block_size_rows_b,
								      int block_size_cols_b,
								      torch::Tensor dense_out);

torch::Tensor blocksparse_matmul_transpose_cublas(torch::Tensor dense_a,
												  torch::Tensor dense_b,
												  torch::Tensor dense_out);

torch::Tensor blocksparse_matmul_cutlass(torch::Tensor dense_a,
 												   torch::Tensor row_ends_b,
												   torch::Tensor cols_b,
												   torch::Tensor data_b,
												   int size_rows_b,
												   int size_cols_b,
												   int block_size_rows_b,
												   int block_size_cols_b,
												   torch::Tensor dense_out);


torch::Tensor blocksparse_matmul_transpose_cuda_(torch::Tensor dense_a,
												torch::Tensor row_ends_b,
												torch::Tensor cols_b,
												torch::Tensor data_b,
												int size_rows_b,
												int size_cols_b,
												int block_size_rows_b,
												int block_size_cols_b,
												torch::Tensor dense_out)
{
    return blocksparse_matmul_transpose_cuda(dense_a, row_ends_b, cols_b, data_b, size_rows_b, size_cols_b, block_size_rows_b, block_size_cols_b, dense_out);
}
#if 0
torch::Tensor blocksparse_matmul_transpose_cublas_dense_(torch::Tensor dense_a,
                                                 torch::Tensor dense_b,
   								                 torch::Tensor dense_out)
{
    return blocksparse_matmul_transpose_cublas(dense_a, dense_b, dense_out);
}
#endif

// dense_a is transposed version of dense_a to be used (problem of pytorch / cutlass integration)
torch::Tensor blocksparse_matmul_cutlass_(torch::Tensor dense_a_t,
                                 torch::Tensor row_ends_b,
                                 torch::Tensor cols_b,
                                 torch::Tensor data_b,
                                 int n,
								 int k,
								 int block_size_rows_b,
								 int block_size_cols_b,
								 torch::Tensor dense_out)
{
    return blocksparse_matmul_cutlass(dense_a_t, row_ends_b, cols_b, data_b, n, k, block_size_rows_b, block_size_cols_b, dense_out);
}


PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("blocksparse_matmul_transpose_cuda", &blocksparse_matmul_transpose_cuda_, "blocksparse_matmul_transpose_cuda");
  //m.def("blocksparse_matmul_transpose_cublas_dense", &blocksparse_matmul_transpose_cublas_dense_, "blocksparse_matmul_transpose_cublas_dense");
  m.def("blocksparse_matmul_cutlass", &blocksparse_matmul_cutlass_, "blocksparse_matmul_cutlass");

}