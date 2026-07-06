void entrypoint() {
    using namespace galigned_stl;

    aligned_vector<int, 16> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    std::cout << vec.data() << std::endl;

    aligned_list<int, 16> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    std::cout << &*lst.begin() << std::endl;

    aligned_set<int, 16> set;
    set.insert(1);
    set.insert(2);
    set.insert(3);
    std::cout << &*set.begin() << std::endl;
}
