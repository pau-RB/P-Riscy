
`ifdef BSV_ASSIGNMENT_DELAY
`else
 `define BSV_ASSIGNMENT_DELAY
`endif

// Dual-Ported BRAM (WRITE FIRST)
module BRAM2(CLKA,
             ENA,
             WEA,
             ADDRA,
             DIA,
             DOA,
             CLKB,
             ENB,
             WEB,
             ADDRB,
             DIB,
             DOB
             );

   parameter                      PIPELINED  = 0;
   parameter                      ADDR_WIDTH = 1;
   parameter                      DATA_WIDTH = 1;
   parameter                      MEMSIZE    = 1;

   input                          CLKA;
   input                          ENA;
   input                          WEA;
   input [ADDR_WIDTH-1:0]         ADDRA;
   input [DATA_WIDTH-1:0]         DIA;
   output [DATA_WIDTH-1:0]        DOA;

   input                          CLKB;
   input                          ENB;
   input                          WEB;
   input [ADDR_WIDTH-1:0]         ADDRB;
   input [DATA_WIDTH-1:0]         DIB;
   output [DATA_WIDTH-1:0]        DOB;

   reg [DATA_WIDTH-1:0]           RAM[0:MEMSIZE-1] /* synthesis syn_ramstyle="no_rw_check" */ ;
   reg [DATA_WIDTH-1:0]           DOA_R;
   reg [DATA_WIDTH-1:0]           DOB_R;
   reg [DATA_WIDTH-1:0]           DOA_R2;
   reg [DATA_WIDTH-1:0]           DOB_R2;

`ifdef ASIC_SYN
   wire[DATA_WIDTH-1:0]           SDOA;
   wire[DATA_WIDTH-1:0]           SDOB;
   reg [DATA_WIDTH-1:0]           SDOA_R;
   reg [DATA_WIDTH-1:0]           SDOB_R;
genvar i;
generate
   if (MEMSIZE == 512 && DATA_WIDTH == 512) begin
      for (i=0; i < 8; i=i+1) begin
         R2PV_512x64 R2PV_512x64_inst(
            .T_LOGIC (1'b0),
            .MA_SAWL (1'b0),
            .MA_TPA (1'b0),
            .MA_TPB (1'b0),
            .MA_WL (1'b0),
            .MA_WRAS (1'b0),
            .MA_WRASD (1'b0),
            .POWERGATE (1'b0),
            .DEEPSLEEP (1'b0),
            .CLK_A (CLKA),
            .CLK_B (CLKB),
            .D (DIB[i*64+63:i*64]),
            .Q (SDOA[i*64+63:i*64]),
            .AC_A (ADDRA[1:0]),
            .AW_A (ADDRA[8:2]),
            .AC_B (ADDRB[1:0]),
            .AW_B (ADDRB[8:2]),
            .BW ({64{WEB}}),
            .CEN_A (ENA),
            .CEN_B (ENB),
            .OBSV_DBW (),
            .OBSV_CTL_A (),
            .OBSV_CTL_B ()
         );
      end
      assign SDOB = SDOA;

      always @(posedge CLKA) begin
         SDOA_R <= `BSV_ASSIGNMENT_DELAY SDOA;
      end

      always @(posedge CLKB) begin
         SDOB_R <= `BSV_ASSIGNMENT_DELAY SDOB;
      end

      // Output drivers
      assign DOA = (PIPELINED) ? SDOA_R : SDOA;
      assign DOB = (PIPELINED) ? SDOB_R : SDOB;

   end else if (MEMSIZE == 256 && DATA_WIDTH == 512) begin
      for (i=0; i < 8; i=i+1) begin
         R2PV_256x64 R2PV_256x64_inst(
            .T_LOGIC (1'b0),
            .MA_SAWL (1'b0),
            .MA_TPA (1'b0),
            .MA_TPB (1'b0),
            .MA_WL (1'b0),
            .MA_WRAS (1'b0),
            .MA_WRASD (1'b0),
            .POWERGATE (1'b0),
            .DEEPSLEEP (1'b0),
            .CLK_A (CLKA),
            .CLK_B (CLKB),
            .D (DIB[i*64+63:i*64]),
            .Q (SDOA[i*64+63:i*64]),
            .AC_A (ADDRA[1:0]),
            .AW_A (ADDRA[7:2]),
            .AC_B (ADDRB[1:0]),
            .AW_B (ADDRB[7:2]),
            .BW ({64{WEB}}),
            .CEN_A (ENA),
            .CEN_B (ENB),
            .OBSV_DBW (),
            .OBSV_CTL_A (),
            .OBSV_CTL_B ()
         );
      end
      assign SDOB = SDOA;

      always @(posedge CLKA) begin
         SDOA_R <= `BSV_ASSIGNMENT_DELAY SDOA;
      end

      always @(posedge CLKB) begin
         SDOB_R <= `BSV_ASSIGNMENT_DELAY SDOB;
      end

      // Output drivers
      assign DOA = (PIPELINED) ? SDOA_R : SDOA;
      assign DOB = (PIPELINED) ? SDOB_R : SDOB;

   end else if (MEMSIZE == 128 && DATA_WIDTH == 512) begin
      for (i=0; i < 8; i=i+1) begin
         R2PV_128x64 R2PV_128x64_inst(
            .T_LOGIC (1'b0),
            .MA_SAWL (1'b0),
            .MA_TPA (1'b0),
            .MA_TPB (1'b0),
            .MA_WL (1'b0),
            .MA_WRAS (1'b0),
            .MA_WRASD (1'b0),
            .POWERGATE (1'b0),
            .DEEPSLEEP (1'b0),
            .CLK_A (CLKA),
            .CLK_B (CLKB),
            .D (DIB[i*64+63:i*64]),
            .Q (SDOA[i*64+63:i*64]),
            .AC_A (ADDRA[1:0]),
            .AW_A (ADDRA[6:2]),
            .AC_B (ADDRB[1:0]),
            .AW_B (ADDRB[6:2]),
            .BW ({64{WEB}}),
            .CEN_A (ENA),
            .CEN_B (ENB),
            .OBSV_DBW (),
            .OBSV_CTL_A (),
            .OBSV_CTL_B ()
         );
      end
      assign SDOB = SDOA;

      always @(posedge CLKA) begin
         SDOA_R <= `BSV_ASSIGNMENT_DELAY SDOA;
      end

      always @(posedge CLKB) begin
         SDOB_R <= `BSV_ASSIGNMENT_DELAY SDOB;
      end

      // Output drivers
      assign DOA = (PIPELINED) ? SDOA_R : SDOA;
      assign DOB = (PIPELINED) ? SDOB_R : SDOB;

   end else if (MEMSIZE == 512 && DATA_WIDTH == 26 ) begin
       R2PV_512x26 R2PV_512x26_inst(
        .T_LOGIC (1'b0),
        .MA_SAWL (1'b0),
        .MA_TPA (1'b0),
        .MA_TPB (1'b0),
        .MA_WL (1'b0),
        .MA_WRAS (1'b0),
        .MA_WRASD (1'b0),
        .POWERGATE (1'b0),
        .DEEPSLEEP (1'b0),
        .CLK_A (CLKA),
        .CLK_B (CLKB),
        .D (DIB),
        .Q (SDOA),
        .AC_A (ADDRA[1:0]),
        .AW_A (ADDRA[8:2]),
        .AC_B (ADDRB[1:0]),
        .AW_B (ADDRB[8:2]),
        .BW ({32{WEB}}),
        .CEN_A (ENA),
        .CEN_B (ENB),
        .OBSV_DBW (),
        .OBSV_CTL_A (),
        .OBSV_CTL_B ()
      );
      assign SDOB = SDOA;

      always @(posedge CLKA) begin
         SDOA_R <= `BSV_ASSIGNMENT_DELAY SDOA;
      end

      always @(posedge CLKB) begin
         SDOB_R <= `BSV_ASSIGNMENT_DELAY SDOB;
      end

      // Output drivers
      assign DOA = (PIPELINED) ? SDOA_R : SDOA;
      assign DOB = (PIPELINED) ? SDOB_R : SDOB;

   end else if (MEMSIZE == 256 && DATA_WIDTH == 26 ) begin
       R2PV_256x26 R2PV_256x26_inst(
        .T_LOGIC (1'b0),
        .MA_SAWL (1'b0),
        .MA_TPA (1'b0),
        .MA_TPB (1'b0),
        .MA_WL (1'b0),
        .MA_WRAS (1'b0),
        .MA_WRASD (1'b0),
        .POWERGATE (1'b0),
        .DEEPSLEEP (1'b0),
        .CLK_A (CLKA),
        .CLK_B (CLKB),
        .D (DIB),
        .Q (SDOA),
        .AC_A (ADDRA[1:0]),
        .AW_A (ADDRA[7:2]),
        .AC_B (ADDRB[1:0]),
        .AW_B (ADDRB[7:2]),
        .BW ({32{WEB}}),
        .CEN_A (ENA),
        .CEN_B (ENB),
        .OBSV_DBW (),
        .OBSV_CTL_A (),
        .OBSV_CTL_B ()
      );
      assign SDOB = SDOA;

      always @(posedge CLKA) begin
         SDOA_R <= `BSV_ASSIGNMENT_DELAY SDOA;
      end

      always @(posedge CLKB) begin
         SDOB_R <= `BSV_ASSIGNMENT_DELAY SDOB;
      end

      // Output drivers
      assign DOA = (PIPELINED) ? SDOA_R : SDOA;
      assign DOB = (PIPELINED) ? SDOB_R : SDOB;

   end else if (MEMSIZE == 128 && DATA_WIDTH == 26 ) begin
       R2PV_128x26 R2PV_128x26_inst(
        .T_LOGIC (1'b0),
        .MA_SAWL (1'b0),
        .MA_TPA (1'b0),
        .MA_TPB (1'b0),
        .MA_WL (1'b0),
        .MA_WRAS (1'b0),
        .MA_WRASD (1'b0),
        .POWERGATE (1'b0),
        .DEEPSLEEP (1'b0),
        .CLK_A (CLKA),
        .CLK_B (CLKB),
        .D (DIB),
        .Q (SDOA),
        .AC_A (ADDRA[1:0]),
        .AW_A (ADDRA[6:2]),
        .AC_B (ADDRB[1:0]),
        .AW_B (ADDRB[6:2]),
        .BW ({32{WEB}}),
        .CEN_A (ENA),
        .CEN_B (ENB),
        .OBSV_DBW (),
        .OBSV_CTL_A (),
        .OBSV_CTL_B ()
      );
      assign SDOB = SDOA;

      always @(posedge CLKA) begin
         SDOA_R <= `BSV_ASSIGNMENT_DELAY SDOA;
      end

      always @(posedge CLKB) begin
         SDOB_R <= `BSV_ASSIGNMENT_DELAY SDOB;
      end

      // Output drivers
      assign DOA = (PIPELINED) ? SDOA_R : SDOA;
      assign DOB = (PIPELINED) ? SDOB_R : SDOB;

   end else begin

      always @(posedge CLKA) begin
         if (ENA) begin
            if (WEA) begin
               RAM[ADDRA] <= `BSV_ASSIGNMENT_DELAY DIA;
               DOA_R <= `BSV_ASSIGNMENT_DELAY DIA;
            end
            else begin
               DOA_R <= `BSV_ASSIGNMENT_DELAY RAM[ADDRA];
            end
         end
         DOA_R2 <= `BSV_ASSIGNMENT_DELAY DOA_R;
      end

      always @(posedge CLKB) begin
         if (ENB) begin
            if (WEB) begin
               RAM[ADDRB] <= `BSV_ASSIGNMENT_DELAY DIB;
               DOB_R <= `BSV_ASSIGNMENT_DELAY DIB;
            end
            else begin
               DOB_R <= `BSV_ASSIGNMENT_DELAY RAM[ADDRB];
            end
         end
         DOB_R2 <= `BSV_ASSIGNMENT_DELAY DOB_R;
      end

      // Output drivers
      assign DOA = (PIPELINED) ? DOA_R2 : DOA_R;
      assign DOB = (PIPELINED) ? DOB_R2 : DOB_R;

   end
endgenerate

`else 

   `ifdef BSV_NO_INITIAL_BLOCKS
   `else
      // synopsys translate_off
      integer                        i;
      initial
      begin : init_block
         for (i = 0; i < MEMSIZE; i = i + 1) begin
            RAM[i] = { ((DATA_WIDTH+1)/2) { 2'b10 } };
         end
         DOA_R = { ((DATA_WIDTH+1)/2) { 2'b10 } };
         DOB_R = { ((DATA_WIDTH+1)/2) { 2'b10 } };
         DOA_R2 = { ((DATA_WIDTH+1)/2) { 2'b10 } };
         DOB_R2 = { ((DATA_WIDTH+1)/2) { 2'b10 } };
      end
      // synopsys translate_on
   `endif // !`ifdef BSV_NO_INITIAL_BLOCKS

   always @(posedge CLKA) begin
      if (ENA) begin
         if (WEA) begin
            RAM[ADDRA] <= `BSV_ASSIGNMENT_DELAY DIA;
            DOA_R <= `BSV_ASSIGNMENT_DELAY DIA;
         end
         else begin
            DOA_R <= `BSV_ASSIGNMENT_DELAY RAM[ADDRA];
         end
      end
      DOA_R2 <= `BSV_ASSIGNMENT_DELAY DOA_R;
   end

   always @(posedge CLKB) begin
      if (ENB) begin
         if (WEB) begin
            RAM[ADDRB] <= `BSV_ASSIGNMENT_DELAY DIB;
            DOB_R <= `BSV_ASSIGNMENT_DELAY DIB;
         end
         else begin
            DOB_R <= `BSV_ASSIGNMENT_DELAY RAM[ADDRB];
         end
      end
      DOB_R2 <= `BSV_ASSIGNMENT_DELAY DOB_R;
   end

   // Output drivers
   assign DOA = (PIPELINED) ? DOA_R2 : DOA_R;
   assign DOB = (PIPELINED) ? DOB_R2 : DOB_R;

`endif

endmodule // BRAM2
