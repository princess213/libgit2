#include "clar_libgit2.h"

static git_oid id;
static git_oid idp;
static git_oid idm;
const char *str_oid = "ae90f12eea699729ed24555e40b9fd669da12a12";
const char *str_oid_p = "ae90f12eea699729ed";
const char *str_oid_m = "ae90f12eea699729ed24555e40b9fd669da12a12THIS IS EXTRA TEXT THAT SHOULD GET IGNORED";

void test_core_oid__initialize(void)
{
	cl_git_pass(git_oid_fromstr(&id, str_oid));
	cl_git_pass(git_oid_fromstrp(&idp, str_oid_p));
	cl_git_fail(git_oid_fromstrp(&idm, str_oid_m));
}

void test_core_oid__streq(void)
{
	cl_assert(git_oid_streq(&id, str_oid) == 0);
	cl_assert(git_oid_streq(&id, "deadbeefdeadbeefdeadbeefdeadbeefdeadbeef") == -1);

	cl_assert(git_oid_streq(&id, "deadbeef") == -1);
	cl_assert(git_oid_streq(&id, "I'm not an oid.... :)") == -1);
	
	cl_assert(git_oid_streq(&idp, "ae90f12eea699729ed0000000000000000000000") == 0);
	cl_assert(git_oid_streq(&idp, "deadbeefdeadbeefdeadbeefdeadbeefdeadbeef") == -1);

	cl_assert(git_oid_streq(&idp, "deadbeef") == -1);
	cl_assert(git_oid_streq(&idp, "I'm not an oid.... :)") == -1);
}
