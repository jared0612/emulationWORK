#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <cppconn/statement.h>
#include <cppconn/resultset.h>

using namespace std;
using namespace sql;

int main() {
    try {
        mysql::MySQL_Driver *driver = mysql::get_mysql_driver_instance();
        unique_ptr<Connection> conn(driver->connect("tcp://127.0.0.1:3306", "root", "0612"));
        conn->setSchema("mydb");

        unique_ptr<Statement> stmt(conn->createStatement());
        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT * FROM students"));

        while (res->next()) {
            cout << "ID: " << res->getInt("id") << ", Name: " << res->getString("name") << endl;
        }
    } catch (SQLException &e) {
        cerr << "MySQL 错误: " << e.what() << endl;
        return 1;
    }
    return 0;
}
