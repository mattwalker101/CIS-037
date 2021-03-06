/* Homework 11.11
 * Matthew Walker, Windows VS2012
 * Write statements to initialize a file, write 10 records, update a record, and delete a record
 * 
 */

#include <stdio.h>
#include <string.h>

#define FILENAME "nameage.txt"

struct person {
	char lastName[ 15 ];
	char firstName[ 15 ];
	char age[ 4 ];
};

int menuOptions( void );
void createBlank( void );
void updateRecord( void );
void addTenRecord( void );
void deleteRecord( void );
void showFile( void );


int main()
{

	int choice;

	while ( ( choice = menuOptions() ) != 5 ) {
		switch( choice ) {
		case 1:
			createBlank();	//create a text file with 100 blank entries
                        showFile();
			break;
		case 2:
			updateRecord();  // change values in one record 
			showFile();
                        break;
		case 3:
			addTenRecord();  // append 10 entries with user input
			showFile();
                        break;
		case 4:
			deleteRecord(); // delete a record specified by user
			showFile;
                        break;
		default:
			puts( "Invalid choice!\n" );
			break;
		}
	}

	return 0;
}

void createBlank( void )     // a) Initialize the file with 100 blank entries
{
	FILE *createPtr;
	int i;
	struct person pData = { "unassigned", "", "0" };

	if ( ( fopen_s( &createPtr, FILENAME, "r+" ) ) != 0 ) {
		puts( "File could not be opened.\n" );
	} else { // initialize with 100 blank records
		for ( i = 0; i < 100; i++ ) {
			fwrite( &pData, sizeof( pData ), 1, createPtr );
		}
	}

	fclose( createPtr );
}


void addTenRecord( void )   // b) Input 10 last names, first names and ages, and write them to the file
{
	FILE *addPtr;
	int i;
	struct person pData;
	
	if ( ( fopen_s( &addPtr, FILENAME, "a" ) ) != 0 ) {
		puts( "Cannot open the file to append!\n" );
	} else {
		for ( i = 0; i < 10; i++ ) { // loop 10 times
			printf( "Enter the last name to be added: " );
			scanf_s( "%s", &pData.lastName );  // store user data in struct pData
	
			printf( "Enter the first name to be added: " );
			scanf_s( "%s", &pData.firstName );

			printf( "Enter the age to be added: " );
			scanf_s( "%s", &pData.age );

			// write all the data to the file using pointer to file cfPtr
			fwrite( &pData, sizeof( pData ), 1, addPtr );
		}

		fclose( addPtr );
	}
}


void updateRecord( void )    // c) update a record
{
	FILE *updatePtr;
	struct person pData;
	char lName[ 15 ];

	if ( ( fopen_s( &updatePtr, FILENAME, "r+" ) ) != 0 ) {
		puts( "Trouble opening file for updating!\n" );
	} else {
		printf( "Enter the last name of the person whose record you wish to update: " );
		scanf_s( "%s", &lName );

		while ( ( fread( &pData, sizeof( pData ), 1, updatePtr ) ) ) {
			if ( strcmp ( pData.lastName, lName ) == 0 ) { // when there is a match...
				printf( "Enter the new data for that record : \n\n" );
				printf( "\nEnter the lastname for that record : " );
				scanf_s( "%s", &pData.lastName );
				printf( "\nEnter the firstname for that record : " );
				scanf_s( "%s", &pData.firstName );
				printf( "\nEnter the age for that record : " );
				scanf_s( "%s", &pData.age );

				fwrite( &pData, sizeof( pData ), 1, updatePtr );
			}
		}
		fclose( updatePtr );
	}

}

void deleteRecord( void )       // d) delete a record
{
	FILE *deletePtr;
	struct person pData;
	char lName[ 15 ];

	if ( ( fopen_s( &deletePtr, FILENAME, "r+" ) ) != 0 ) {
		puts( "Problem opening the file for deletion!\n" );
	} else {
		printf( "Enter the last name of the record you wish to delete : " );
		scanf_s( "%s", lName );

		while ( fread( &pData, sizeof( pData ), 1, deletePtr ) ) {
			if ( strcmp ( pData.lastName, lName ) == 0 ) { // when there is a match...
				strcpy( pData.lastName, "unassigned" );  // place unassigned in last name
				strcpy( pData.firstName, "" ); // "" in firstName
				strcpy( pData.age, "0" ); // and 0 for age

				fseek( deletePtr, sizeof( pData ), SEEK_CUR );  // find position of record in cfPtr to be deleted

				fwrite( &pData, sizeof ( pData ), 1, deletePtr );
			}
		}
		fclose( deletePtr );

	}
}

int menuOptions( void )
{
	int mChoice; 

	printf( "/nWhat would you like to do today?\n" 
			"(1) to create a new text file with 100 blank entries,\n" 
			"(2) to update a single record,\n"
			"(3) to add 10 user generated records,\n"
			"(4) to delete a single record, or\n"
			"(5) to end the program.\n" );
	scanf( "%d", &mChoice );
	return mChoice;
}

void showFile( void )
{
	FILE *showPtr;
	struct person pData;

	if ( ( fopen_s( &showPtr, FILENAME, "r" ) ) != 0 ) {
		puts( "Can't open file for display!\n" );
	} else {
		while ( fread( &pData, sizeof( pData ), 1, showPtr ) ) {
			printf( "%-16s%-16s%-5s\n", pData.lastName, pData.firstName, pData.age );
		}
	}
	fclose( showPtr );
}

