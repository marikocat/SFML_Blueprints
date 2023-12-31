#include  <ORM/backends/MySql/MySqlDB.hpp>
#include  <ORM/backends/MySql/MySqlQuery.hpp>

#include <ORM/fields/private/VAttr.hpp>
#include <ORM/backends/op.hpp>
#include <ORM/core/macros.hpp>

#include <sstream>

//#include <my_global.h>

#include <mutex>

std::mutex _counterMutex;
int _counter = 0;

namespace orm
{
    MySqlTableCreator MySqlDB::_creator;

    MySqlDB::MySqlDB(const std::string& username,const std::string& pass,const std::string& db,const std::string& serveur,int port) :
        DB(username,pass,db,serveur,port),
        _dbConn(nullptr) // a pointer to a database connection object
    {
        // filter
        _operators[op::exact]= " = %s";
        _operators[op::iexact]= " LIKE %s";
        _operators[op::contains]= " LIKE BINARY %s";
        _operators[op::icontains]= " LIKE %s";
        _operators[op::regex]= " REGEXP BINARY %s";
        _operators[op::iregex]= " REGEXP %s";
        _operators[op::gt]= " > %s";
        _operators[op::gte]= " >= %s";
        _operators[op::lt]= " < %s";
        _operators[op::lte]= " <= %s";
        _operators[op::startswith]= " LIKE BINARY %s";
        _operators[op::endswith]= " LIKE BINARY %s";
        _operators[op::istartswith]= " LIKE %s";
        _operators[op::iendswith]= " LIKE %s";

        // ordering
        _operators["?"] = " RAND() ";
        _operators["+"] = " ASC ";
        _operators["-"] = " DESC ";

        {
            std::lock_guard<std::mutex> guard(_counterMutex);
            if (_counter++ == 0)
            {
                // Call this function to initialize the MySQL client library before you call any other MySQL function.
                if (mysql_library_init(0, nullptr, nullptr))
                {
                    std::cerr << "Unable to initialize MySQL library" << std::endl;
                }
            }
        }

        //escape_char = "";
    };

    MySqlDB::~MySqlDB()
    {
        disconnect();

        {
            std::lock_guard<std::mutex> guard(_counterMutex);
            if (--_counter == 0)
            {
                mysql_library_end();
            }
        }

    };

    std::shared_ptr<orm::DB> MySqlDB::clone()const
    {
        return std::shared_ptr<orm::DB>(new MySqlDB(this->_username,this->_password,this->_dbName,this->_serveur,this->_port));
    }

    bool MySqlDB::connect()
    {
        _dbConn = mysql_init(nullptr); // Allocates or initializes a MYSQL object suitable for mysql_real_connect(). If mysql is a NULL pointer, the function allocates, initializes, and returns a new object.
        if(_dbConn == nullptr)
        {
            std::cerr << "Could not get a database driver. Error message: "<< mysql_error(_dbConn) <<std::endl;
            return false;
        }

        // attempts to establish a connection to a MySQL server running on host
        if (mysql_real_connect(_dbConn, _serveur.c_str(), _username.c_str(), _password.c_str(),
            _dbName.c_str(), _port, nullptr /* socket*/, 0 /*flags*/) == nullptr)
        {
            std::cerr << "Could not connect to database. Error message: " << mysql_error(_dbConn) << std::endl;
            disconnect();
            return false;
        }
        else
            std::cout << "Connected to db " << _dbName.c_str() << std::endl;

        return true;
    };

    bool MySqlDB::disconnect()
    {
        bool res = false;
        if(_dbConn)
        {
            mysql_close(_dbConn);
            _dbConn = nullptr;
            res = true;
        }
        return res;
    };

    void MySqlDB::threadInit()
    {
        mysql_thread_init();
    }

    void MySqlDB::threadEnd()
    {
        mysql_thread_end();
    }

    std::shared_ptr<Query> MySqlDB::query(const std::string& str)
    {
        auto q = std::shared_ptr<Query>(new MySqlQuery(*this,str));
        q->_prepared = false;
        return q;
    };

    std::shared_ptr<Query> MySqlDB::query(std::string&& str)
    {
        return query(str);
    };


    std::shared_ptr<Query> MySqlDB::prepareQuery(const std::string& str)
    {
        auto q = std::shared_ptr<Query>(new MySqlQuery(*this,str));
        q->_prepared = true;
        return q;
    };

    std::shared_ptr<Query> MySqlDB::prepareQuery(std::string&& str)
    {
        return prepareQuery(str);
    }

    bool MySqlDB::create(const std::string& table,const std::vector<const VAttr*>& attrs)
    {
        std::string sql = "CREATE TABLE "+_escapeColumn(table)+"(\n";
        unsigned int size = attrs.size();
        sql+= creator().autoField(ORM_COLUMN_PRIMARY_KEY);

        const DB& db=*this;
        std::vector<std::string> constraints;
        for(unsigned int i=0;i<size;++i)
        {
            std::istringstream iss(attrs[i]->_create(db));
            std::string res;
            std::getline(iss, res, ',');
            sql += ",\n" + res;
            if (std::getline(iss, res, ','))
            {
                constraints.push_back(res);
            }

            //sql+=",\n"+attrs[i]->_create(db);
        }
        for (int i = 0; i < constraints.size(); ++i)
        {
            sql += ",\n" + constraints[i];
        }
        sql+="\n)";
        constraints.clear();
        std::cout << "create table query: " << sql << std::endl;
        std::shared_ptr<Query> q = this->query(sql);
        q->_execute();
        q->_next();

        return true;
    }

    bool MySqlDB::drop(const std::string& table)
    {
        std::string sql = "DROP TABLE "+_escapeColumn(table);

        std::shared_ptr<Query> q = this->query(sql);
        q->_execute();
        q->_next();

        return true;
    }

    bool MySqlDB::clear(const std::string& table)
    {

        std::string sql = "TRUNCATE "+_escapeColumn(table);

        std::shared_ptr<Query> q = this->query(sql);
        q->_execute();
        q->_next();

        return true;
    }

    /************** PROTECTED **********************/

    void MySqlDB::beginTransaction()
    {
        std::shared_ptr<Query> q = this->query("START TRANSACTION");
        q->_execute();
        q->_next();
    };

    void MySqlDB::endTransaction()
    {
        std::shared_ptr<Query> q = this->query("COMMIT");
        q->_execute();
        q->_next();
    };

    void MySqlDB::rollback()
    {
        std::shared_ptr<Query> q = this->query("ROLLBACK");
        q->_execute();
        q->_next();
    };

    int MySqlDB::_getLastInsertPk()
    {
        std::shared_ptr<Query> q = query("SELECT LAST_INSERT_ID()");

        q->_execute();
        q->_next();

        int pk = -1;
        q->_get(pk,_getInitialGetcolumnNumber());

        return pk;
    }

    std::string MySqlDB::_escapeColumn(const std::string& str) const
    {
        return "`"+str+"`";
    }

    int MySqlDB::_getInitialGetcolumnNumber() const
    {
        return 0;
    }

    int MySqlDB::_getInitialSetcolumnNumber() const
    {
        return 0;
    }

    std::string MySqlDB::_limit(const int& skip,const int& count)const
    {
        std::string query;
        if(skip > 0 and count > 0)
        {
            query+=" LIMIT "+std::to_string(skip)+" , "+std::to_string(count);
        }
        else if (count > 0)
        {
            query+=" LIMIT "+std::to_string(count);
        }
        else
        {
            std::cerr<<ORM_COLOUR_RED<<"[ERROR] Limit : count can't be <= 0"<<std::endl;
        }
        return query;
    };

    const TableCreator& MySqlDB::creator() const
    {
        return _creator;
    }

};
