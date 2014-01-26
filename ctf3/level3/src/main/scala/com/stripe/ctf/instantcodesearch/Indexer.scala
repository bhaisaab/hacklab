package com.stripe.ctf.instantcodesearch

import java.io._
import java.util.Arrays
import java.nio.file._
import java.nio.charset._
import java.nio.file.attribute.BasicFileAttributes

class Indexer(indexPath: String, indexId : Int) {
  val root = FileSystems.getDefault().getPath(indexPath)
  val idx = new Index(root.toAbsolutePath.toString, indexId)
  val indexerId = indexId
  var counter : Int = 0

  def index() : Indexer = {
    walkFS(root)
    //idx.closeLuceneWriter()
    System.out.println("Walk over, let's query!")
    return this
  }

  def walkFS(startDir : Path) {
    Files.walkFileTree(startDir, new SimpleFileVisitor[Path] {
      override def preVisitDirectory(dir : Path, attrs : BasicFileAttributes) : FileVisitResult = {
        if (Files.isHidden(dir) && dir.toString != ".")
          return FileVisitResult.SKIP_SUBTREE
        return FileVisitResult.CONTINUE
      }
      override def visitFile(file : Path, attrs : BasicFileAttributes) : FileVisitResult = {
        if (Files.isHidden(file))
          return FileVisitResult.CONTINUE
        if (!Files.isRegularFile(file, LinkOption.NOFOLLOW_LINKS))
          return FileVisitResult.CONTINUE
        if (Files.size(file) > (1 << 20))
          return FileVisitResult.CONTINUE
         try {
            //idx.addLuceneFile(root.relativize(file).toString, file)
            idx.addFile(root.relativize(file).toString, file)
        } catch {
          case e: IOException => {
            System.out.println("EXCEPTION! " + e)
            return FileVisitResult.CONTINUE
          }
        }

        return FileVisitResult.CONTINUE
      }
    })
  }

  def write(path: String) = {
    idx.write(new File(path))
  }
}
