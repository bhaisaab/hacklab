package com.stripe.ctf.instantcodesearch

import scala.collection.mutable.{ HashMap, MultiMap, Set, HashSet }
import scala.collection.concurrent._

import java.io._
import java.nio.file._
import java.util._
import java.nio.charset._


import org.apache.lucene.analysis.core.WhitespaceAnalyzer
import org.apache.lucene.analysis.Analyzer._
import org.apache.lucene.analysis.standard._
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

class Index(repoPath: String, idxId : Int) extends Serializable {
  val indexId = idxId
  var reverseIndex = new HashMap[String, Set[Tuple2[Int, Int]]] with MultiMap[Int, Tuple2[Int, Int]]
  var fileLookup = new HashMap[Int, String]

  var analyzer = new WhitespaceAnalyzer(Version.LUCENE_40)
  var directory = new RAMDirectory()
  var config = new IndexWriterConfig(Version.LUCENE_40, analyzer)
  var iwriter = new IndexWriter(directory, config)

  var counter : Int = 0

  def path() = repoPath

  def addLuceneFile(fileName : String, file: Path) {
    if (counter % 3 == (indexId - 1)) {
        val reader =  new BufferedReader(new FileReader(file.toString))
        var lineNumber = 1
        var line = ""
        while (line != null) {
            line = reader.readLine()
            if (line != null) {
                var doc = new Document()
                doc.add(new Field("title", fileName + ":" + lineNumber.toString, TextField.TYPE_STORED))
                doc.add(new Field("content", line, TextField.TYPE_STORED))
                iwriter.addDocument(doc)
                lineNumber += 1
            }
        }
        System.out.print("\rlucene-indexing file: " + fileName)
    }
    counter += 1
  }

  def closeLuceneWriter() {
      iwriter.close()
  }

  def addFile(fileName : String, file: Path) {
      if (counter % 3 == (indexId - 1)) {
          val reader =  new BufferedReader(new FileReader(file.toString))
          var lineNumber = 1
          var line = ""
          fileLookup(counter) = "\"" + fileName + ":"
          while (line != null) {
              line = reader.readLine()
              if (line != null) {
                  for (word <- line.split(" ").filter(_.size > 2)) {
                      reverseIndex.addBinding(word, Tuple2(counter, lineNumber))
                  }
                  lineNumber += 1
              }
          }
          System.out.print("\rfile: " + fileName)
      }
      counter += 1
  }

  def write(out: File) {
    val stream = new FileOutputStream(out)
    write(stream)
    stream.close
  }

  def write(out: OutputStream) {
    val w = new ObjectOutputStream(out)
    w.writeObject(this)
    w.close
  }
}

