#include <eosio/eosio.hpp>

using namespace eosio;

CONTRACT registry : public contract {
  public:
    using contract::contract;

    ACTION registerdid(name owner, checksum256 ddoHash);
    ACTION updatedid(name owner, checksum256 new_ddoHash);
    
  private:
  //scope is owner
    TABLE records {
      name    owner;
      checksum256 ddoHash;
      auto primary_key() const { return owner.value; }
    };
    using records_index = multi_index<"records"_n, records>;
};