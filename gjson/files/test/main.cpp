void entrypoint() {
    using namespace gjson;

    auto node = JsonNode::MakeObject();
    node["key"] = JsonNode::MakeString("value");
    node["key2"] = JsonNode::MakeArray();
    node["key2"].getArray().push_back(JsonNode::MakeString("value2"));
    node.print();

    std::cout << std::endl;

    auto node2 = JsonNode::Parse(gdata::Data::MakeFromFile("./info.json"));
    node2.print();
}
