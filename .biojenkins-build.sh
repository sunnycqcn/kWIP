
set -xe

export wdir=`pwd`

test -d khmer-src || git clone https://github.com/ged-lab/khmer khmer-src

# update and install khmer
pushd khmer-src
    git fetch --all
    git reset --hard origin/master
    rm -rf $wdir/khmer
    mkdir $wdir/khmer
    pushd lib
        make install PREFIX=$wdir/khmer/
    popd
popd


# Build kmerclust
rm -rf build
mkdir build
pushd build
    cmake $wdir -DKHMER_ROOT=$wdir/khmer/
    make
    make test
popd

# DISABLED: too hard to get the instructions working without messing up the readme
# check that we can follow the instructions provided for installation
# rm -rf $wdir/install_test
# mkdir $wdir/install_test
# pushd $wdir/install_test
#     # Process: extract commands, change home directory to above, run
#     grep '^    ' $wdir/README.md | sed 's,$HOME,$wdir/install_test,g' | bash -xe
# popd
