#ifndef TENSOR_H
#define TENSOR_H

#include <stdbool.h>
#include <stdlib.h>

#define TENSOR_AT_FLAT(dtype, tensor_ptr, index)                               \
    ((dtype *)((tensor_ptr)->data) + index)

#define TENSOR_AT(dtype, tensor_ptr, indices_array)                            \
    ((dtype *)((tensor_ptr)->data) +                                           \
     compute_flat_index(tensor_ptr, indices_array))

#define tensor_at_int32(tensor_ptr, indices_array)                             \
    TENSOR_AT(int, tensor_ptr, indices_array)

#define tensor_at_flat_int32(tensor_ptr, index)                                \
    TENSOR_AT_FLAT(int, tensor_ptr, index)

#define tensor_at_float32(tensor_ptr, indices_array)                           \
    TENSOR_AT(float, tensor_ptr, indices_array)

#define tensor_at_flat_float32(tensor_ptr, index)                              \
    TENSOR_AT_FLAT(float, tensor_ptr, index)

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
    bool owns_data;
} Tensor;

Tensor *create_tensor(const size_t *shape, size_t dims, Datatype dtype);
Tensor *create_tensor_with_data(const size_t *shape, size_t dims,
                                Datatype dtype, void *data);
void free_tensor(Tensor *tensor);

size_t compute_flat_index(const Tensor *tensor, const size_t *indices);
// computed the strides given an array on n dimensions
size_t *compute_strides(const size_t *shape, size_t n);

void reshape(Tensor *tensor, const size_t *shape, size_t ndim);
Tensor *slice(const Tensor *original, const size_t *start, const size_t *end);

// prints information about the tensor
void print_info(const Tensor *tensor);

static inline float tensor_get_flat_int32(Tensor *t, size_t i)
{
    return *tensor_at_flat_int32(t, i);
}

static inline float tensor_get_flat_float32(Tensor *t, size_t i)
{
    return *tensor_at_flat_float32(t, i);
}

#endif // TENSOR_H
