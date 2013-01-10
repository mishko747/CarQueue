#ifndef DELIMITER
	#define DELIMITER ,	 // Delimiter between elements of the enum
#endif

#ifndef ENUMERATION_BEGIN
	#define ENUMERATION_BEGIN(arg) enum arg {	// Beginning of the enum
#endif

#ifndef ENUMERATION_END
	#ifdef LAST_ENUMERATOR
		#define ENUMERATION_END DELIMITER LAST_ENUMERATOR }	// last item in the enum
	#else
		#define ENUMERATION_END }	// End of the enum
	#endif
#endif

#ifndef DECLARE_MEMBER
	#define DECLARE_MEMBER(arg) arg	// Item of the enum
#endif

#ifndef MEMBER_VALUE
	#define MEMBER_VALUE(arg) = arg	// Value of the item
#endif