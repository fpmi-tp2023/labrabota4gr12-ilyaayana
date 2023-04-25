#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "DROP TABLE IF EXISTS COMPANY;" 
      "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );"
      "DROP TABLE IF EXISTS Cars;" 
      "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
      "INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
      "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
      "INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
      "INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
      "INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
      "INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
      "INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
      "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

                               
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
