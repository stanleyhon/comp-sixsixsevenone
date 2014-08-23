#!/usr/bin/perl -w

%tests = ( "Word", "Pine",
           "Pizza", "Pills",
           "Aura", "Will",
           "Asleep", "Awake",
           "Hungry", "Thirst",
           "Red", "Met",
           "Green", "Speed",
           "Run", "Pun",
           "Coy", "Met",
           "Cog", "Pug");

while (($key, $value) = each (%tests)) {
    print "Testing $key -> $value...\n";
    open (INFILE, ">infile") or die "Couldn't open infile\n";
    print INFILE "$key\n";
    print INFILE "$value\n";
    close INFILE;

    $myOutput = `./wl < infile`;
    $refOutput = `./wl_ref < infile`;

    if ($myOutput eq $refOutput) {
        print "Passed!\n";
    } else {
        print "Failed!\n";
        print "$myOutput\n";
    }
    
    `rm infile`;
}
