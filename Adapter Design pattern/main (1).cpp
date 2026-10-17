#include <iostream>
#include <string>

// TARGET
// This is the interface our existing application/client expects.
class IDataProcessor {
public:
    virtual void processJSON(const std::string& data) = 0;
    virtual ~IDataProcessor() = default;
};


// ADAPTEE
// Existing/third-party class.
// It only understands XML.
class XMLProcessor {
public:
    void processXML(const std::string& data) {
        std::cout << "XML Processor received:\n"
                  << data << std::endl;
    }
};


// ADAPTER
// Client expects IDataProcessor,
// but XMLProcessor only understands XML.
//
// Adapter converts JSON -> XML and delegates to XMLProcessor.
class XMLAdapter : public IDataProcessor {
private:
    XMLProcessor* xmlProcessor;

public:
    XMLAdapter(XMLProcessor* processor)
        : xmlProcessor(processor) {
    }

    void processJSON(const std::string& json) override {

        std::cout << "Adapter received JSON:\n"
                  << json << std::endl;

        // Simulating JSON -> XML conversion.
        // In a real application, use a proper JSON/XML library.
        std::string xml =
            "<person>"
                "<name>Amarnath</name>"
                "<age>25</age>"
            "</person>";

        std::cout << "\nAdapter converted JSON to XML:\n"
                  << xml << std::endl;

        // Delegate to the existing XML processor
        xmlProcessor->processXML(xml);
    }
};


int main() {

    // Existing component that only understands XML
    XMLProcessor xmlProcessor;

    // Adapter makes XMLProcessor compatible with IDataProcessor
    XMLAdapter adapter(&xmlProcessor);

    // Client works only with the interface it understands
    IDataProcessor* processor = &adapter;

    std::string data =
        R"({"name":"Amarnath","age":25})";

    processor->processJSON(data);

    return 0;
}