import System.IO

main = do end <- isEOF
          if end then putStr ""
          else do input <- getLine
                  if input == "42" then putStr ""
                  else do putStrLn input
                          main
