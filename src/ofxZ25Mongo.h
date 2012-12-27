#pragma once
#include <cstdlib>
//#include <iostream>
#include "mongo/client/dbclient.h"

/*
 * http://api.mongodb.org/cplusplus/2.3.0/classmongo_1_1_d_b_client_interface.html
 * virtual auto_ptr< DBClientCursor > 	query (const string &ns, Query query, int nToReturn=0, int nToSkip=0, const BSONObj *fieldsToReturn=0, int queryOptions=0, int batchSize=0)=0
 * virtual void 	insert (const string &ns, BSONObj obj, int flags=0)=0
 * virtual void 	insert (const string &ns, const vector< BSONObj > &v, int flags=0)=0
 * virtual void 	remove (const string &ns, Query query, bool justOne=0)=0
 * virtual void 	remove (const string &ns, Query query, int flags)=0
 * virtual void 	update (const string &ns, Query query, BSONObj obj, bool upsert=false, bool multi=false)=0
 * virtual void 	update (const string &ns, Query query, BSONObj obj, int flags)=0
 * virtual BSONObj 	findOne (const string &ns, const Query &query, const BSONObj *fieldsToReturn=0, int queryOptions=0)
 * void 	findN (vector< BSONObj > &out, const string &ns, Query query, int nToReturn, int nToSkip=0, const BSONObj *fieldsToReturn=0, int queryOptions=0)
 *      query N objects from the database into an array.
 * virtual string 	getServerAddress () const =0
 * virtual auto_ptr< DBClientCursor > 	getMore (const string &ns, long long cursorId, int nToReturn=0, int options=0)=0
 * 	don't use this - called automatically by DBClientCursor for you 
 */

using namespace mongo;

class ofxZ25MongoClient : public DBClientConnection {

public:
	ofxZ25MongoClient();
	~ofxZ25MongoClient();

	//void connect(std::string url);
	//bool connect(string url, string &errmsg); //eventueel met string& errormsg

//protected:
    //mongo::DBClientConnection c;
    std::auto_ptr<mongo::DBClientCursor> cursor;
};
