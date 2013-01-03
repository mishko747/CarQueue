#ifndef DELIMITER
	#define DELIMITER ,
#endif

#ifndef ENUMERATION_BEGIN
	#define ENUMERATION_BEGIN(arg) enum arg {
#endif

#ifndef ENUMERATION_END
	#ifdef LAST_ENUMERATOR
		#define ENUMERATION_END DELIMITER LAST_ENUMERATOR }
	#else
		#define ENUMERATION_END }
	#endif
#endif

#ifndef DECLARE_MEMBER
	#define DECLARE_MEMBER(arg) arg
#endif

#ifndef MEMBER_VALUE
	#define MEMBER_VALUE(arg) = arg
#endif