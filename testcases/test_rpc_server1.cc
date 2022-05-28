#include <google/protobuf/service.h>
#include "tcp_server.h"
#include "net_address.h"
#include "tinypb_rpc_dispatcher.h"
#include "log.h"
#include "tinyrpc/comm/start.h"
#include "tinypb.pb.h"
#include "coroutine_hook.h"
#include "tinyrpc/comm/start.h"
#include "tinyrpc/comm/mysql_instase.h"
#include "tinyrpc/comm/start.h"
#include <mysql/mysql.h>
#include <sstream>

// // tinyrpc::Config::ptr gRpcConfig;

class QueryServiceImpl : public QueryService {
 public:
  QueryServiceImpl() {}
  ~QueryServiceImpl() {}

  void query_name(google::protobuf::RpcController* controller,
                       const ::queryNameReq* request,
                       ::queryNameRes* response,
                       ::google::protobuf::Closure* done) {
    
    // DebugLog << "========================";
    // DebugLog << "this is query_name func";
    // DebugLog << "first begin to sleep 6s";
    // sleep_hook(6);
    // DebugLog << "sleep 6s end";

    response->set_ret_code(0);
    response->set_res_info("OK");

    // tinyrpc::MySQLInstase* instase =  tinyrpc::MySQLInstaseFactroy::GetThreadMySQLFactory()->GetMySQLInstase("test_db_key1");
    // if (!instase->isInitSuccess()) {
    //   response->set_ret_code(-1);
    //   response->set_res_info("faild to init mysql");
    //   ErrorLog << "mysql instase init failed";
    //   return;
    // }

    // char query_sql[512];
    // sprintf(query_sql, "select user_id, user_name, user_gender from user_db.t_user_information where user_id = '%s';", std::to_string(request->id()).c_str());

    // int rt = instase->query(std::string(query_sql));
    // if (rt != 0) {
    //   response->set_ret_code(-1);
    //   response->set_res_info(instase->getMySQLErrorInfo());
    //   ErrorLog << "failed to excute sql" << std::string(query_sql);
    //   return;
    // }

    // MYSQL_RES* res = instase->storeResult();

    // MYSQL_ROW row = instase->fetchRow(res);
    // if (row) {
    //   int i = 0;
    //   DebugLog << "query success";
    //   response->set_id(std::atoi(row[i++]));
    //   response->set_name(std::string(row[i++]));
    // } else {
    //   DebugLog << "query empty";
    //   response->set_ret_code(-1);
    //   response->set_res_info("this user not exist");
    // }
    response->set_id(request->id());
    response->set_name("ikerli");
    if (done) {
      done->Run();
    }
  }

  void query_age(google::protobuf::RpcController* controller,
                       const ::queryAgeReq* request,
                       ::queryAgeRes* response,
                       ::google::protobuf::Closure* done) {

    DebugLog << "========================";
    DebugLog << "this is query_age func";
    response->set_ret_code(0);
    response->set_res_info("OK");
    response->set_req_no(request->req_no());
    response->set_id(request->id());
    response->set_age(20);
    DebugLog << "========================";
    done->Run();
  }

};


int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Start TinyRPC server error, input argc is not 2!");
    printf("Start TinyRPC server like this: \n");
    printf("./server a.xml\n");
    return 0;
  }

  tinyrpc::InitConfig(argv[1]);

  tinyrpc::GetServer()->registerService(std::make_shared<QueryServiceImpl>());

  tinyrpc::StartRpcServer();
  
  return 0;
}
