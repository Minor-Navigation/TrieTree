import java.io.BufferedWriter;
import java.io.FileWriter;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;

public class MongoDBJDBC {

	public static void main(String args[]) {

		try {
			
			BufferedWriter bw = null;
			FileWriter fw = null;
			fw = new FileWriter("mongo_node_data.txt");
			bw = new BufferedWriter(fw);
			
			MongoClient mongo = new MongoClient("localhost", 27017);

			/**** Get database ****/
			// if database doesn't exists, MongoDB will create it for you
			DB db = mongo.getDB("osm_india");

			/**** Get collection / table from 'testdb' ****/
			// if collection doesn't exists, MongoDB will create it for you
			DBCollection table = db.getCollection("nodes");

			/****
			 * Insert *** // create a document to store key and value
			 * BasicDBObject document = new BasicDBObject();
			 * document.put("name", "mkyong"); document.put("age", 30); //
			 * document.put("createdDate", new Date()); table.insert(document);
			 */

			/**** Find and display ****/

			// BasicDBObject searchQuery = new BasicDBObject();

			// db.getCollection("nodes").find({ tags.name: { $exists: true } }
			// );

			DBObject query = new BasicDBObject("tags.name", new BasicDBObject("$exists", true));
			DBCursor result = table.find(query);
			System.out.println(result.size());
			//int i = 0;
			long id = 0;
			Double lati = null, longi = null;
			String name = null;
			while (result.hasNext()) {
				//i++;
				DBObject obj = result.next();
				DBObject tag = (DBObject) (obj.get("tags"));
				DBObject loc = (DBObject) (obj.get("loc"));

				// double loc[] = (double[]) (obj.get("loc"));

				name = (String) (tag.get("name"));
				name = name.toLowerCase();
				longi = (Double) (loc.get("0"));
				lati = (Double) (loc.get("1"));

				id = (long) (obj.get("id"));
				//bw.write("name=" + name + " id=" + id + " longi= " + longi + " lati=" + lati+"\n");
				bw.write(name + "$" + id + "$" + longi + "$" + lati+"$\n");
				

				//System.out.println("name=" + name + " id=" + id + " longi=" + longi + " lati=" + lati);

				
			}
			bw.close();
			fw.close();

			// ({"IMAGE URL":{$ne:null}}) ;
			// searchQuery.put("name", "mkyong");

			// DBCursor cursor = table.find(searchQuery);
			//
			// while (cursor.hasNext()) {
			// System.out.println(cursor.next());
			// }
			//
			// /**** Update ****/
			// // search document where name="mkyong" and update it with new
			// values
			// BasicDBObject query = new BasicDBObject();
			// query.put("name", "mkyong");
			//
			// BasicDBObject newDocument = new BasicDBObject();
			// newDocument.put("name", "mkyong-updated");
			//
			//
			// BasicDBObject updateObj = new BasicDBObject();
			// updateObj.put("$set", newDocument);
			// updateObj.append("$currentDate", new
			// BasicDBObject().append("lastModified", true));
			//
			// table.update(query, updateObj);
			//
			// /**** Find and display ****/
			// BasicDBObject searchQuery2
			// = new BasicDBObject().append("name", "mkyong-updated");
			//
			// DBCursor cursor2 = table.find(searchQuery2);
			//
			// while (cursor2.hasNext()) {
			// System.out.println(cursor2.next());
			// }
			//
			// /**** Done ****/
			// System.out.println("Done");

		} catch (Exception e) {
			System.err.println(e.getClass().getName() + ": " + e.getMessage());
		}
	}
}

