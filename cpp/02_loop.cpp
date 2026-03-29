// 四种循环
// 手动控制 → 抽象表达 → 并行执行 → 声明式数据流

// 传统索引 for 循环，C++98标准
for(size_t i=0;i<players.size();++i) {
    if (players[i].hp==0.f)players[i].hp=100.f;
}

// 范围 for 循环，C++11标准
for (auto& player : players) {
    if (player.hp == 0.f) {
        player.hp = 100.f;
    }
}

// 并行算法，parallel STL，C++17标准
// seq：顺序执行
// par：多线程并行
// unseq：向量化（SIMD）
// par_unseq：并行 + SIMD，无序执行，指令重排，但要求无数据竞争且无顺序竞争
std::for_each(std::execution::par_unseq, players.begin(), players.end(),
    [](auto& player) {
        if (player.hp == 0.f) {
            player.hp = 100.f;
        }
    }
);

// 声明式数据流，ranges库，C++20标准
// lazy + pipeline + 声明式
auto dead_players = players | std::views::filter([](const auto& p) {
    return p.hp == 0.f;
});
std::ranges::for_each(dead_players, [](auto& p) { p.hp=100.f; });
