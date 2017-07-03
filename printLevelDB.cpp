#include <iostream>
#include <algorithm>
#include "common.h"
#include <leveldb/db.h>
#include <json/json.h>
using namespace std;

int main() {

    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, LVFILECHUNK, &db);
    printf("status:%d\n", status.ok());
    if(!status.ok()) {
        return 0;
    }
    cout << "-------" << LVFILECHUNK << "-------" << endl;
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
    }
    delete it;
    delete db;
    status = leveldb::DB::Open(options, LVFILEDIR, &db);
    if(!status.ok()) {
        return 0;
    }
    cout << "-------" << LVFILEDIR<< "-------" << endl;
    it = db->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
    }
    delete it;
    delete db;

}
