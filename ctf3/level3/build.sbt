import AssemblyKeys._

resolvers += "twitter" at "http://maven.twttr.com/"

resolvers += "retronym-releases" at "http://retronym.github.com/repo/releases"

resolvers ++= Seq(
  "snapshots" at "http://oss.sonatype.org/content/repositories/snapshots",
  "releases"  at "http://oss.sonatype.org/content/repositories/releases"
)


libraryDependencies += "com.twitter" %% "twitter-server" % "1.0.2"

libraryDependencies += "com.twitter" %% "finagle-core" % "6.5.2"

libraryDependencies += "com.twitter" %% "finagle-stream" % "6.5.2"

libraryDependencies += "org.rogach" %% "scallop" % "0.9.4"

libraryDependencies += "org.apache.lucene" % "lucene-core" % "4.6.0"

libraryDependencies += "org.apache.lucene" % "lucene-queries" % "4.6.0"

libraryDependencies += "org.apache.lucene" % "lucene-analyzers-common" % "4.6.0"

libraryDependencies += "org.apache.lucene" % "lucene-queryparser" % "4.6.0"

libraryDependencies += "org.apache.lucene" % "lucene-memory" % "4.6.0"

assemblySettings

jarName in assembly := "level3.jar"

outputPath in assembly := file("./level3.jar")

mergeStrategy in assembly <<= (mergeStrategy in assembly) { (old) =>
  {
    case PathList("com", "twitter", "common", "args", xs @ _*) => MergeStrategy.last
    case x => old(x)
  }
}

scalacOptions ++= Seq("-feature", "-deprecation")
