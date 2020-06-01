#include <registry.hpp>

ACTION registry::registerdid(name owner, checksum256 ddoHash) {
    require_auth(owner);

    records_index records_table(get_self(), owner.value );
    
    auto records_itr = records_table.find(owner.value);
    check( records_itr == records_table.end(), "A DID has been registered for this account");
    records_table.emplace( get_self(), [&]( auto& record ){
        record.owner = owner;
        record.ddoHash = ddoHash;
    });
}


ACTION registry::updatedid(name owner, checksum256 new_ddoHash) {
    require_auth(owner);

    records_index records_table(get_self(), owner.value );

    auto records_itr = records_table.find(owner.value);
    check( records_itr != records_table.end(), "No DID has been registered for this account");
    records_table.modify(records_itr, get_self(), [&]( auto& record ){
        record.owner = owner;
        record.ddoHash = new_ddoHash;
    });
}