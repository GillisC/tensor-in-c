#ifndef TENSOR_H
#define TENSOR_H

#include <stdlib.h>

#define TENSOR_AT(dtype, tensor_ptr, indices_array)                            \
    ((dtype *)((tensor_ptr)->data) +                                           \
     compute_flat_index(tensor_ptr, indices_array))

// The actual size of data type depends on the system
typedef enum
{
    DT_FLOAT,
    DT_INT,
} Datatype;

typedef struct
{
    void *data;
    Datatype dtype;
    size_t *shape;
    size_t *strides;
    size_t ndim;
    size_t size;
} Tensor;

Tensor *create_tensor(const size_t *shape, size_t dims, Datatype dtype);
Tensor *create_tensor_with_data(const size_t *shape, size_t dims,
                                Datatype dtype, void *data);
void free_tensor(Tensor *tensor);

size_t compute_flat_index(const Tensor *tensor, const size_t *indices);
// computed the strides given an array on n dimensions
size_t *compute_strides(const size_t *shape, size_t n);

// prints information about the tensor
void print_info(const Tensor *tensor);

#endif // TENSOR_H
