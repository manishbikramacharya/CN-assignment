#define ASIO_STANDALONE
#include "asio.hpp"
#include "crow_all.h"
#include <fstream>
#include <iostream>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([](){
        return R"(
            <!DOCTYPE html>
            <html>
            <head>
                <title>File Upload</title>
            </head>
            <body>
                <h1>File Upload</h1>
                <form action="/upload" method="post" enctype="multipart/form-data">
                    <input type="file" name="file">
                    <input type="submit" value="Upload">
                </form>
            </body>
            </html>
        )";
    });

    CROW_ROUTE(app, "/upload")
        .methods("POST"_method)
    ([](const crow::request& req, crow::response& res){
        std::string filename = "uploaded_file"; // Default filename
        std::string content = req.body;

        // Save the file
        std::ofstream out_file("uploads/" + filename, std::ios::binary);
        if (out_file) {
            out_file.write(content.c_str(), content.size());
            out_file.close();
            res.code = 200;
            res.write("File uploaded successfully");
        } else {
            res.code = 500;
            res.write("Failed to save file");
        }
        res.end();
    });

    app.port(8080).multithreaded().run();
}
