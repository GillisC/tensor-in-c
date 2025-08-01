
#include <stdbool.h>
#include <stdio.h>

#include "tensor.h"

int main()
{
    size_t shape[3] = {2, 3};
    float data[6] = { 1.f, 2.f, 3.f, 4.f, 5.f, 6.f };
    Tensor *t = create_tensor_with_data(shape, 2, DT_FLOAT, data);

    print_info(t);

    size_t indices[2] = {1, 1};
    float *a = TENSOR_AT(float, t, indices);
    printf("at 1, 1: %f", *a);

    free_tensor(t);
    return 0;
}
