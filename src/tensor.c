#include "tensor.h"

#include <stdio.h>
#include <string.h>

Tensor *create_tensor(const size_t *shape, size_t dims, Datatype dtype) 
{
    Tensor *tensor = malloc(sizeof(Tensor));
    tensor->shape = malloc(sizeof(size_t) * dims);
    tensor->ndim = dims;
    tensor->strides = compute_strides(shape, dims);

    size_t elements = 1;
    for (size_t dim = 0; dim < dims; dim++) {
        tensor->shape[dim] = shape[dim];
        elements *= shape[dim];
    }

    tensor->size = elements;
    
    switch (dtype) {
        case DT_FLOAT: 
        {
            tensor->data = malloc(sizeof(float) * tensor->size);
            break;
        } 
        case DT_INT: 
        {
            tensor->data = malloc(sizeof(int) * tensor->size);
            break;
        }
    }

    return tensor;
}

size_t sizeof_dtype(Datatype dtype)
{
    switch (dtype) 
    {
        case DT_FLOAT: return sizeof(float);
        case DT_INT: return sizeof(int);
    }
    return 0;
}

Tensor *create_tensor_with_data(const size_t *shape, size_t dims, Datatype dtype, void *data) 
{
    Tensor *t = create_tensor(shape, dims, dtype);
    if (!t) {
        fprintf(stderr, "error creating tensor");
        exit(1);
    }
    memcpy(t->data, data, t->size * sizeof_dtype(t->dtype));
    return t;
}

void free_tensor(Tensor *tensor) {
    free(tensor->shape);
    free(tensor->data);
    free(tensor);
}

size_t *compute_strides(const size_t *shape, size_t n) 
{
    size_t *strides = malloc(sizeof(size_t) * n);
    for (size_t i = 0; i < n; i++) 
    {
        size_t stride_product = 1; 
        for (size_t j = i + 1; j < n; j++) {
            stride_product *= shape[j];
        }
        strides[i] = stride_product;
    }
    return strides;
}


size_t compute_flat_index(const Tensor *tensor, const size_t *indices) {
    size_t index = 0;
    for (size_t i = 0; i < tensor->ndim; i++) 
    {
        index += indices[i] * tensor->strides[i];
    }
    return index;
}

void print_info(const Tensor *tensor) 
{
    printf("shape: ");
    for (size_t i = 0; i < tensor->ndim; i++)
    {
        printf("%zu ", tensor->shape[i]);
    }
    putchar('\n');

    printf("strides: ");
    for (size_t i = 0; i < tensor->ndim; i++)
    {
        printf("%zu ", tensor->strides[i]);
    }
    putchar('\n');
    printf("ndim: %zu\n", tensor->ndim);
    printf("size: %zu\n", tensor->size);
}



