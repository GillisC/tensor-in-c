#include "testa.h"
#include "tensor.h"

#include <stdio.h>

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
