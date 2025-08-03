#include "testa.h"
#include "tensor.h"

#include <stdio.h>

// Test:
// content of a tensor
// stride computation for larger tensors
// correct flat index calculation
// 

TEST(tensor_initialization) {
    size_t shape[2] = {2, 2};
    Tensor *t = create_tensor(shape, 2, DT_FLOAT);

    // valid pointer?
    ASSERT_NOT_NULL(t);

    // shape
    size_t expected_ndims = 2;
    ASSERT_EQ_SIZE_T(t->ndim, expected_ndims);
    size_t expected1 = 2;
    size_t expected2 = 2;
    ASSERT_EQ_SIZE_T(t->shape[0], expected1);
    ASSERT_EQ_SIZE_T(t->shape[1], expected2);

    // strides
    size_t expected_stride1 = 2;
    size_t expected_stride2 = 1;
    ASSERT_EQ_SIZE_T(t->strides[0], expected_stride1);
    ASSERT_EQ_SIZE_T(t->strides[1], expected_stride2);

    size_t expected_size = 4;
    ASSERT_EQ_SIZE_T(t->size, expected_size);

    free_tensor(t);
}

TEST(tensor_reshape) {
    size_t shape[2] = { 2, 3 };
    float data[6] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f };
    Tensor *t = create_tensor_with_data(shape, sizeof(shape) / sizeof(size_t), DT_FLOAT, data);

    ASSERT_NOT_NULL(t);
    ASSERT_EQ_SIZE_T(t->ndim, (size_t)(2));
    ASSERT_EQ_SIZE_T(t->shape[0], (size_t)(2));
    ASSERT_EQ_SIZE_T(t->shape[1], (size_t)(3));
    ASSERT_EQ_SIZE_T(t->strides[0], (size_t)(3));
    ASSERT_EQ_SIZE_T(t->strides[1], (size_t)(1));

    for (size_t i = 0; i < t->size; i++)
    {
        ASSERT_EQ_FLOAT(*tensor_at_flat_float32(t, i), i + 1.f, 0.00001);
    }

    size_t new_shape[2] = { 3, 2 };
    reshape(t, new_shape, 2);

    ASSERT_EQ_SIZE_T(t->size, (size_t)(6));
    ASSERT_EQ_SIZE_T(t->shape[0], (size_t)(3));
    ASSERT_EQ_SIZE_T(t->shape[1], (size_t)(2));
    ASSERT_EQ_SIZE_T(t->strides[0], (size_t)(2));
    ASSERT_EQ_SIZE_T(t->strides[1], (size_t)(1));

    for (size_t i = 0; i < t->size; i++)
    {
        ASSERT_EQ_FLOAT(*tensor_at_flat_float32(t, i), i + 1.f, 0.00001);
    }

    free_tensor(t);
}

TEST(tensor_slice)
{
    size_t shape[2] = { 3, 3 };
    float data[9] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f };
    Tensor *t = create_tensor_with_data(shape, sizeof(shape) / sizeof(size_t), DT_FLOAT, data);

    ASSERT_EQ_SIZE_T(t->size, (size_t)(9));

    size_t start[2] = {1, 1};
    size_t end[2] = {3, 3};
    Tensor *sliced = slice(t, start, end);
    
    ASSERT_EQ_SIZE_T(sliced->size, (size_t)(4));
    ASSERT_EQ_SIZE_T(sliced->ndim, (size_t)(2));
    ASSERT_FALSE(sliced->owns_data);
    ASSERT_EQ_SIZE_T(sliced->shape[0], (size_t)(2));
    ASSERT_EQ_SIZE_T(sliced->shape[1], (size_t)(2));
    ASSERT_EQ_FLOAT(*tensor_at_flat_float32(sliced, 0), 5.f, 0.0001);

    float expected[4] = { 5.f, 6.f, 8.f, 9.f };
    for (size_t i = 0; i < sliced->shape[0]; i++)
    {
        for (size_t j = 0; j < sliced->shape[1]; j++)
        {
            size_t indices[2] = { i, j };
            printf("%f", *tensor_at_float32(sliced, indices));
            // ASSERT_EQ_FLOAT(*tensor_at_float32(sliced, indices), expected[i], 0.00001);
        }
    }
    free_tensor(sliced);
    free_tensor(t);
}
