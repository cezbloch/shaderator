typedef struct { global int *bar; } Foo;
kernel void vectorAdd(global const Foo* aNum, global const int *inputA, global const int *inputB,
  global int *output, int val, write_only pipe int outPipe, queue_t childQueue)
{
  output[get_global_id(0)] = inputA[get_global_id(0)] + inputB[get_global_id(0)] + val + *(aNum->bar);
  write_pipe(outPipe, &val);
  queue_t default_queue = get_default_queue();
  ndrange_t ndrange = ndrange_1D(get_global_size(0) / 2, get_global_size(0) / 2);
  // Have a child kernel write into third quarter of output
  enqueue_kernel(default_queue, CLK_ENQUEUE_FLAGS_WAIT_KERNEL, ndrange,
    ^{
      output[get_global_size(0) * 2 + get_global_id(0)] =
      inputA[get_global_size(0) * 2 + get_global_id(0)] + inputB[get_global_size(0) * 2 + get_global_id(0)] + globalA;
    });
  // Have a child kernel write into last quarter of output
  enqueue_kernel(childQueue, CLK_ENQUEUE_FLAGS_WAIT_KERNEL, ndrange,
    ^{
      output[get_global_size(0) * 3 + get_global_id(0)] =
      inputA[get_global_size(0) * 3 + get_global_id(0)] + inputB[get_global_size(0) * 3 + get_global_id(0)] + globalA + 2;
    });
}