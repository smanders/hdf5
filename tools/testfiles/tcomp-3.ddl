#############################
Expected output for 'h5dump -t /#5992:0 -g /group2 tcompound.h5'
#############################
HDF5 "tcompound.h5" {
DATATYPE "/#5992:0" {
   H5T_STD_I32BE "int";
   H5T_IEEE_F32BE "float";
}
GROUP "/group2" {
   DATASET "dset5" {
      DATATYPE {
         "#5992:0"
      }
      DATASPACE { SIMPLE ( 5 ) / ( 5 ) }
      DATA {
         {0,0}
         {1,0.1}
         {2,0.2}
         {3,0.3}
         {4,0.4}
      }
   }
}
}
