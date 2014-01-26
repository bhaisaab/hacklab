package com.stripe.ctf.instantcodesearch

import java.io._
import java.nio.file._

import com.twitter.concurrent.Broker

import org.apache.lucene.analysis.Analyzer
import org.apache.lucene.analysis.standard.StandardAnalyzer
import org.apache.lucene.document.Document
import org.apache.lucene.document.Field
import org.apache.lucene.document.LongField
import org.apache.lucene.document.StringField
import org.apache.lucene.document.TextField
import org.apache.lucene.index.DirectoryReader
import org.apache.lucene.index.IndexReader
import org.apache.lucene.index.IndexWriter
import org.apache.lucene.index.IndexWriterConfig
import org.apache.lucene.index.IndexWriterConfig.OpenMode
import org.apache.lucene.index.Term
import org.apache.lucene.queryparser.classic.QueryParser
import org.apache.lucene.search.IndexSearcher
import org.apache.lucene.search.Query
import org.apache.lucene.store.Directory
import org.apache.lucene.store.FSDirectory
import org.apache.lucene.store.RAMDirectory
import org.apache.lucene.util.Version

abstract class SearchResult
case class Match(path: String) extends SearchResult
case class Done() extends SearchResult

class Searcher(indexPath : String)  {
  var index : Index = new Index("/tmp", 0)//readIndex(indexPath)
  var indexId : Int = -1
  val root = FileSystems.getDefault().getPath(index.path)
  val idxPath = indexPath

  def search(needle : String, b : Broker[SearchResult]) = {
      for (tupSet <- index.reverseIndex.filterKeys{ key => key.contains(needle) }.values) {
          tupSet.map { tupe =>
               b !! new Match(index.fileLookup(tupe._1) + tupe._2.toString + "\"")
          }
      }
      //if (index.reverseIndex.contains(needle)) {
      //    index.reverseIndex(needle).map { tupe =>
      //        b !! new Match(index.fileLookup(tupe._1) + tupe._2.toString + "\"")
      //    }
      //}
    b !! new Done()
  }

  def searchLucene(needle : String, b : Broker[SearchResult]) = {
      var ireader = DirectoryReader.open(index.directory)
      var isearcher = new IndexSearcher(ireader)
      var parser = new QueryParser(Version.LUCENE_40, "content", index.analyzer)
      parser.setAllowLeadingWildcard(true)
      var query = parser.parse("[a-zA-Z]*" + needle + "[a-zA-Z]*")
      var hits = isearcher.search(query, null, 10000).scoreDocs
      var answer = ""

      var i = 0
      while (i < hits.length) {
          var doc = isearcher.doc(hits(i).doc)
          b !! new Match(doc.get("title"))
          i += 1
      }
      if (answer != "")
          b !! new Match(answer)
    b !! new Done()
  }

  def setIndex(idx : Index, id : Int) = {
      index = idx
      indexId = id
  }

   def readIndex(path: String) : Index = {
    new ObjectInputStream(new FileInputStream(new File(path))).readObject.asInstanceOf[Index]
  }
}
