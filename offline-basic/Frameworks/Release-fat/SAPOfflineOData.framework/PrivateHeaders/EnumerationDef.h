//
//  EnumerationDef.h
//  SAPOfflineOData
//
//  Copyright © 2017 SAP SE or an SAP affiliate company. All rights reserved.
//
//  No part of this publication may be reproduced or transmitted in any form or for any purpose
//  without the express permission of SAP SE.  The information contained herein may be changed
//  without prior notice.
//


#import <Foundation/Foundation.h>



typedef NS_ENUM(NSInteger, ResponseTypeObjC)
{


	 RESPONSE_NOT_SET = 0,
	 	 RESPONSE_ERROR = 1,
	 	 RESPONSE_ENTITY_TYPE = 2,
	 	 RESPONSE_ENTITY_SET = 3,
	 	 RESPONSE_ENTITY_TYPE_PROPERTY = 4,
	 	 RESPONSE_COMPLEX_TYPE_PROPERTY = 5,
	 	 RESPONSE_COMPLEX_TYPE = 6,
	 	 RESPONSE_COUNT = 7,
	 	 RESPONSE_VALUE = 8,
	 	 RESPONSE_METADATA_DOCUMENT = 9,
	 	 RESPONSE_SERVICE_DOCUMENT = 10,
	 	 RESPONSE_LINK = 11,
	 	 RESPONSE_LINKS = 12,
	 	 RESPONSE_MEDIA_STREAM = 13,
	

};

typedef NS_ENUM(NSInteger, EdmTypeObjC) {


	 EDM_BINARY = 1,
	 	 EDM_BOOLEAN = 2,
	 	 EDM_BYTE = 3,
	 	 EDM_DATETIME = 4,
	 	 EDM_DATETIME_OFFSET = 5,
	 	 EDM_DECIMAL = 6,
	 	 EDM_DOUBLE = 7,
	 	 EDM_GUID = 8,
	 	 EDM_INT16 = 9,
	 	 EDM_INT32 = 10,
	 	 EDM_INT64 = 11,
	 	 EDM_SINGLE = 12,
	 	 EDM_SBYTE = 13,
	 	 EDM_STRING = 14,
	 	 EDM_TIME = 15,
	 	 EDM_BOOLEAN_BYTE = 2000,
	 	 EDM_NULL = 2001,
	 	 EDM_SBYTE_POSITIVE = 2002,
	 	 EDM_SBYTE_NEGATIVE = 2003,
	

};

typedef NS_ENUM(NSInteger,MethodObjC )
{


	 METHOD_NOT_SET = 0,
	 	 METHOD_GET = 1,
	 	 METHOD_POST = 2,
	 	 METHOD_PUT = 3,
	 	 METHOD_PATCH = 4,
	 	 METHOD_DELETE = 5,
	

};

typedef NS_ENUM(NSInteger, BatchItemTypeObjC)
{


 	 BATCH_ITEM_SINGLE = 0,
	 	 BATCH_ITEM_CHANGESET = 1,
	

};

typedef NS_ENUM(NSInteger, LogLevelObjC)
{


 	 NONE_LOG_LEVEL = 0,
	 	 FATAL_LOG_LEVEL = 1,
	 	 ERROR_LOG_LEVEL = 2,
	 	 WARNING_LOG_LEVEL = 3,
	 	 INFO_LOG_LEVEL = 4,
	 	 DEBUG_LOG_LEVEL = 5,
	 	 ALL_LOG_LEVEL = 6,
	

};

#if defined( DEV )



typedef NS_ENUM(NSInteger, LODataContextObjC )
{


 	 LODATA_TEST_SYNC_OBSERVER_OBJC = 0,
	 	 LODATA_TEST_SYNC_INTERRUPTED_OBJC = 1,
	 	 LODATA_TEST_DELETE_LINKS_OBJC = 2,
	 	 LODATA_TEST_BEFORE_DOWNLOAD_DB_OBJC = 3,
	 	 LODATA_TEST_FOUND_COMMAND_OBJC = 4,
	 	 LODATA_TEST_NEW_DB_OBJC = 5,
	 	 LODATA_TEST_BEFORE_EXECUTE_BATCH_OBJC = 6,
	 	 LODATA_TEST_BEFORE_EXECUTE_REQUEST_OBJC = 7,
	 	 LODATA_TEST_FILE_TRANSFER_OBSERVER_OBJC = 8,
	

};

typedef NS_ENUM(NSInteger, ULSyncState )
{
	ULSYNC_NOT_SYNCHRONIZING = 1,
	ULSYNC_CONNECTING = 2,
	ULSYNC_WAITING = 3,
	ULSYNC_SENDING = 4,
	ULSYNC_RECEIVING = 5,
	ULSYNC_PROCESSING = 6,
	ULSYNC_DONE = 7
};

#endif
