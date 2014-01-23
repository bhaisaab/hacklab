package main

import (
    "os"
    "crypto/sha1"
    "fmt"
    "time"
    "encoding/hex"
)

func mine(difficulty, workproof string, i, j int, result chan string) {
    hashes := 0
    now := time.Now()
    start_second := now.Truncate(time.Second)
    for ;j > i; i++ {
        body := fmt.Sprintf("%s%x\n", workproof, i)
        git_body := fmt.Sprintf("commit %d\x00%s", len(body), body)
        h := sha1.New()
        h.Write([]byte(git_body))
        sum := h.Sum(nil)
        cs := hex.EncodeToString(sum[:])
        if cs < difficulty {
            result <- body
            break
        }
        hashes++
        now := time.Now()
        end_second := now.Truncate(time.Second)
        if end_second.After(start_second) {
                fmt.Fprintln(os.Stderr, "hashes per second:", hashes)
                start_second = end_second
                hashes = 0
        }
    }
}

func main() {
    tree := os.Args[1]
    parent := os.Args[2]
    difficulty := os.Args[3]
    ts := time.Now().Unix()
    hash :=make(chan string)

    work := fmt.Sprintf("tree %s\nparent %s\nauthor bhaisaab <bhaisaab@baagi.org> %d +0000\ncommitter bhaisaab <bhaisaab@baagi.org> %d +0000\n\nI can haz gitcoins\n", tree, parent, ts, ts)

    for i:= 0; i < 10; i++ {
        go mine(difficulty, work, i * 10000000, (i+1) * 10000000, hash)
    }
    fmt.Printf("%s", <- hash)
}
