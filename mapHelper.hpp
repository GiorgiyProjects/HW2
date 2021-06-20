struct mapHelper {
    template<typename T>
    void fillMap(T &m, const int size) {
        m[0] = 1;
        for (int i = 1; i < 10; ++i) {
            m[i] = m[i - 1] * i;
        }
    }

    template<typename T>
    std::string printMap(const T& m) {
        std::string result = "";
        std::for_each(m.begin(),
                      m.end(),
                      [&result](const auto &p) {
                          result += std::to_string(p.first) + " " + std::to_string(p.second) + ";";
                          return result;
                      });
        result += '\n';
        return result;
    }
};