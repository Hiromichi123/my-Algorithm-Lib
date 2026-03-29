// 缓存 cache
// CPU访问内存的速度远慢于CPU的处理速度，导致性能瓶颈。
// 为了弥补这个差距，现代CPU引入了多级缓存（L1、L2、L3），将频繁访问的数据存储在更快的缓存中，以提高访问速度。

// 1.控制访问顺序

// 连续cache miss，导致性能下降
for (int i = 0; i < N; i++) {
    sum += arr[random[i]];
}

// 连续访问，cache命中率高
for (int i = 0; i < N; i++) {
    sum += arr[i];
}

// 二维数组经典坑
int arr[1000][1000];

// 错误顺序：列优先访问，导致频繁cache miss
for (int j = 0; j < 1000; j++) {
    for (int i = 0; i < 1000; i++) {
        arr[i][j] = i + j;
    }
}

// 正确顺序：行优先访问
for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
        arr[i][j] = i + j;
    }
}


// 2.数据局部 AoS（Array of Structures） vs SoA（Structure of Arrays）
// AoS：每个对象的所有属性存储在一起，适合访问单个对象的所有属性，但访问同一属性的多个对象时cache效率低。
struct Player {
    float hp;
    float mp;
    float x, y, z;
};

// SoA：每个属性的所有对象存储在一起，适合访问同一属性的多个对象，cache效率高。
struct Players {
    std::vector<float> hp;
    std::vector<float> mp;
    std::vector<float> x, y, z;
};
