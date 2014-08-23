#!/usr/bin/perl -w

use Time::HiRes qw(time);

%tests = ( "Word", "Pine",
           "Pizza", "Pills",
           "Aura", "Will",
           "Asleep", "Awake",
           "Hungry", "Thirst",
           "Red", "Met",
           "Green", "Speed",
           "Run", "Pun",
           "Coy", "Met",
           "Cog", "Pug",
           "Pug", "cog",
           "cog", "pug",
           "Abbreviations", "Accelerometer",
           "fable", "facer",
           "faked", "faith",
           "fairy", "fling",
           "Cherry", "ridden",
           "  ", "at",
           "bam", "bio",
           "ben", "bar",
           "bin", "bag",
           );

while (($key, $value) = each (%tests)) {
    print "+ Testing $key -> $value...\n";
    open (INFILE, ">infile") or die "Couldn't open infile\n";
    print INFILE "$key\n";
    print INFILE "$value\n";
    close INFILE;

    $timeNow = sprintf ("%.3f", time);
    $myOutput = `./wl < infile`;
    $timeAfter = sprintf ("%.3f", time);;

    $myTimeTaken = $timeAfter - $timeNow;
    printf ("Your Implementation took %.3f s\n", $myTimeTaken) ;

    $timeNow = sprintf ("%.3f", time);
    $refOutput = `./wl_ref < infile`;
    $timeAfter = sprintf ("%.3f", time);
    
    $refTimeTaken = $timeAfter - $timeNow;
    printf ("COMP6771 Implementation took %.3f s\n", $refTimeTaken) ;

    if ($myTimeTaken > $refTimeTaken * 10) {
        print "********WARNING********\n";
        print "Your implementation took longer than 10x reference!\n";
        print "***********************\n\n";
    }

    if ($myOutput eq $refOutput) {
        print "Passed!\n";
    } else {
        print "****************Failed!\n";
        print "$myOutput\n********************\n";
    }
    
    `rm infile`;
}
