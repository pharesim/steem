#pragma once
#include <steem/chain/steem_object_types.hpp>

namespace steem { namespace plugins { namespace account_by_key {

using namespace std;
using namespace steem::chain;

#ifndef STEEM_ACCOUNT_BY_KEY_SPACE_ID
#define STEEM_ACCOUNT_BY_KEY_SPACE_ID 11
#endif

enum account_by_key_object_types
{
   key_lookup_object_type = ( STEEM_ACCOUNT_BY_KEY_SPACE_ID << 8 )
};

class key_lookup_object : public object< key_lookup_object_type, key_lookup_object >
{
   public:
      template< typename Constructor, typename Allocator >
      key_lookup_object( Constructor&& c, allocator< Allocator > a )
      {
         c( *this );
      }

      key_lookup_object() {}

      id_type           id;

      public_key_type   key;
      account_name_type account;
};

typedef key_lookup_object::id_type key_lookup_id_type;

struct by_key;

typedef multi_index_container<
   key_lookup_object,
   indexed_by<
      ordered_unique< tag< by_id >, member< key_lookup_object, key_lookup_id_type, &key_lookup_object::id > >,
      ordered_unique< tag< by_key >,
         composite_key< key_lookup_object,
            member< key_lookup_object, public_key_type, &key_lookup_object::key >,
            member< key_lookup_object, account_name_type, &key_lookup_object::account >
         >
      >
   >,
   allocator< key_lookup_object >
> key_lookup_index;

} } } // steem::plugins::account_by_key


FC_REFLECT( steem::plugins::account_by_key::key_lookup_object, (id)(key)(account) )
CHAINBASE_SET_INDEX_TYPE( steem::plugins::account_by_key::key_lookup_object, steem::plugins::account_by_key::key_lookup_index )
