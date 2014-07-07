#!/bin/sh
CFLAGS='-Wc,LANGLVL(EXTENDED) -Wc,LONGLONG -Wc,XPLINK -Wc,TARGET(zOSV1R9) -O2 '
DEFINES='-D_XOPEN_SOURCE_EXTENDED=1 -D_OPEN_THREADS -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -D_POSIX1_SOURCE=2'
CFLAGS=${CFLAGS}${DEFINES}
CCFLAGS='-+ '
CCFLAGS=${CCFLAGS}${CFLAGS}
ASMFLAGS='-Wa,GOFF, -Wa,XPLINK'

echo "CFLAGS = ${CFLAGS}"
echo "CCFLAGS = ${CCFLAGS}"


echo "Building CXX object mintomic/CMakeFiles/Mintomic.dir/mintomic_zos.s.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintomic && xlC ${ASMFLAGS} -o CMakeFiles/Mintomic.dir/mintomic_zos.s.o   -c /u/wpcuk02/ac2/mintomic/src/mintomic/mintomic_zos.s
echo "Linking C static library libMintomic.a"
cd /u/wpcuk02/ac2/mintomic/tests/mintomic && ar -rc libMintomic.a CMakeFiles/Mintomic.dir/mintomic_zos.s.o
echo "Built target Mintomic"

echo "Building CXX object mintpack/CMakeFiles/MintPack.dir/lwlogger.cpp.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintpack && xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/src/mintpack/../../include    -o CMakeFiles/MintPack.dir/lwlogger.cpp.o -c /u/wpcuk02/ac2/mintomic/src/mintpack/lwlogger.cpp
echo "Building CXX object mintpack/CMakeFiles/MintPack.dir/random.cpp.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintpack && xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/src/mintpack/../../include    -o CMakeFiles/MintPack.dir/random.cpp.o -c /u/wpcuk02/ac2/mintomic/src/mintpack/random.cpp
echo "Building CXX object mintpack/CMakeFiles/MintPack.dir/threadsynchronizer.cpp.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintpack && xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/src/mintpack/../../include    -o CMakeFiles/MintPack.dir/threadsynchronizer.cpp.o -c /u/wpcuk02/ac2/mintomic/src/mintpack/threadsynchronizer.cpp
echo "Building CXX object mintpack/CMakeFiles/MintPack.dir/timewaster.cpp.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintpack && xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/src/mintpack/../../include    -o CMakeFiles/MintPack.dir/timewaster.cpp.o -c /u/wpcuk02/ac2/mintomic/src/mintpack/timewaster.cpp
echo "Linking CXX static library libMintPack.a"
cd /u/wpcuk02/ac2/mintomic/tests/mintpack && ar -rc libMintPack.a CMakeFiles/MintPack.dir/lwlogger.cpp.o CMakeFiles/MintPack.dir/random.cpp.o CMakeFiles/MintPack.dir/threadsynchronizer.cpp.o CMakeFiles/MintPack.dir/timewaster.cpp.o
echo "Built target MintPack"

echo "Building CXX object mintsystem/CMakeFiles/MintSystem.dir/gcc/datetime.c.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintsystem && xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/src/mintsystem/../../include    -o CMakeFiles/MintSystem.dir/gcc/datetime.c.o   -c /u/wpcuk02/ac2/mintomic/src/mintsystem/gcc/datetime.c
echo "Building CXX object mintsystem/CMakeFiles/MintSystem.dir/gcc/mutex.c.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintsystem && xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/src/mintsystem/../../include    -o CMakeFiles/MintSystem.dir/gcc/mutex.c.o   -c /u/wpcuk02/ac2/mintomic/src/mintsystem/gcc/mutex.c
echo "Building CXX object mintsystem/CMakeFiles/MintSystem.dir/xlc/semaphore.c.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintsystem && xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/src/mintsystem/../../include    -o CMakeFiles/MintSystem.dir/xlc/semaphore.c.o   -c /u/wpcuk02/ac2/mintomic/src/mintsystem/xlc/semaphore.c
echo "Building CXX object mintsystem/CMakeFiles/MintSystem.dir/gcc/timer.c.o"
cd /u/wpcuk02/ac2/mintomic/tests/mintsystem && xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/src/mintsystem/../../include    -o CMakeFiles/MintSystem.dir/gcc/timer.c.o   -c /u/wpcuk02/ac2/mintomic/src/mintsystem/gcc/timer.c
cd /u/wpcuk02/ac2/mintomic/tests/mintsystem && xlC ${ASMFLAGS} -o CMakeFiles/MintSystem.dir/xlc/timer.s.o -c /u/wpcuk02/ac2/mintomic/src/mintsystem/xlc/timer.s
echo "Linking C static library libMintSystem.a"
cd /u/wpcuk02/ac2/mintomic/tests/mintsystem && ar -rc libMintSystem.a  CMakeFiles/MintSystem.dir/gcc/datetime.c.o CMakeFiles/MintSystem.dir/gcc/mutex.c.o CMakeFiles/MintSystem.dir/xlc/semaphore.c.o CMakeFiles/MintSystem.dir/gcc/timer.c.o CMakeFiles/MintSystem.dir/xlc/timer.s.o
echo "Built target MintSystem"

cd /u/wpcuk02/ac2/mintomic/tests/
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.main.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.main.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.main.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_add_triangle_32.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_add_triangle_32.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_add_triangle_32.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_add_triangle_64.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_add_triangle_64.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_add_triangle_64.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_bitarray_32_128.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_bitarray_32_128.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_bitarray_32_128.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_bitarray_32_32768.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_bitarray_32_32768.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_bitarray_32_32768.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_bitarray_64_128.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_bitarray_64_128.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_bitarray_64_128.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_bitarray_64_32768.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_bitarray_64_32768.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_bitarray_64_32768.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_increment_32.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_increment_32.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_increment_32.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_increment_64.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_increment_64.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_increment_64.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_linkedlist_32.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_linkedlist_32.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_linkedlist_32.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_linkedlist_64.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_linkedlist_64.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_linkedlist_64.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_load_store_32.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_load_store_32.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_load_store_32.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_load_store_32_fail.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_load_store_32_fail.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_load_store_32_fail.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_load_store_64.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_load_store_64.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_load_store_64.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_load_store_64_fail.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_load_store_64_fail.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_load_store_64_fail.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_32.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_32.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_mutex_acq_rel_32.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_32_fail.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_32_fail.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_mutex_acq_rel_32_fail.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_64.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_64.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_mutex_acq_rel_64.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_64_fail.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_64_fail.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_mutex_acq_rel_64_fail.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_return_values_32.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_return_values_32.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_return_values_32.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_return_values_64.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_return_values_64.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_return_values_64.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_storeload_32.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_storeload_32.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_storeload_32.cpp
echo "Building CXX object CMakeFiles/MintomicTests.dir/generated.test_storeload_32_fail.cpp.o"
xlC ${CCFLAGS} -I/u/wpcuk02/ac2/mintomic/tests/../include    -o CMakeFiles/MintomicTests.dir/generated.test_storeload_32_fail.cpp.o -c /u/wpcuk02/ac2/mintomic/tests/generated.test_storeload_32_fail.cpp
rm MintomicTests
xlC -Wl,EDIT=NO -Wl,xplink ${DEFINES} -oMintomicTests  CMakeFiles/MintomicTests.dir/generated.main.cpp.o CMakeFiles/MintomicTests.dir/generated.test_add_triangle_32.cpp.o CMakeFiles/MintomicTests.dir/generated.test_add_triangle_64.cpp.o CMakeFiles/MintomicTests.dir/generated.test_bitarray_32_128.cpp.o CMakeFiles/MintomicTests.dir/generated.test_bitarray_32_32768.cpp.o CMakeFiles/MintomicTests.dir/generated.test_bitarray_64_128.cpp.o CMakeFiles/MintomicTests.dir/generated.test_bitarray_64_32768.cpp.o CMakeFiles/MintomicTests.dir/generated.test_increment_32.cpp.o CMakeFiles/MintomicTests.dir/generated.test_increment_64.cpp.o CMakeFiles/MintomicTests.dir/generated.test_linkedlist_32.cpp.o CMakeFiles/MintomicTests.dir/generated.test_linkedlist_64.cpp.o CMakeFiles/MintomicTests.dir/generated.test_load_store_32.cpp.o CMakeFiles/MintomicTests.dir/generated.test_load_store_32_fail.cpp.o CMakeFiles/MintomicTests.dir/generated.test_load_store_64.cpp.o CMakeFiles/MintomicTests.dir/generated.test_load_store_64_fail.cpp.o CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_32.cpp.o CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_32_fail.cpp.o CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_64.cpp.o CMakeFiles/MintomicTests.dir/generated.test_mutex_acq_rel_64_fail.cpp.o CMakeFiles/MintomicTests.dir/generated.test_return_values_32.cpp.o CMakeFiles/MintomicTests.dir/generated.test_return_values_64.cpp.o CMakeFiles/MintomicTests.dir/generated.test_storeload_32.cpp.o CMakeFiles/MintomicTests.dir/generated.test_storeload_32_fail.cpp.o mintpack/libMintPack.a mintsystem/libMintSystem.a mintomic/libMintomic.a
echo "Built target MintomicTests"
