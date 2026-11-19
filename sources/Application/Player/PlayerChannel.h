
#ifndef _PLAYER_CHANNEL_H_
#define _PLAYER_CHANNEL_H_

#include "Services/Audio/AudioModule.h"
#include "Application/Instruments/I_Instrument.h"
#include "Application/Mixer/MixBus.h"

class PlayerChannel: public AudioModule {
public:
	PlayerChannel(int index) ;
	virtual ~PlayerChannel() ;
	virtual bool Render(fixed *buffer,int samplecount) ;
	void StartInstrument(I_Instrument *instr,unsigned char note,bool cleanStart) ;
	void StopInstrument() ;
	I_Instrument *GetInstrument() ;
	void SetMute(bool muted) ;
	bool IsMuted() ;
	void SetMixBus(int i) ;
    void SetVolume(fixed volume);
    void SetHPFMode(unsigned char mode);
    void ApplyHPF(fixed *buffer, int samplecount);
    void SetLPFFreq(unsigned short freq);
    void Reset();

    // --- Sidechain ducker (one shared envelope across all channels) ---
    // Config is read once from config.xml (DUCK_ENABLE / DUCK_TRIGGER /
    // DUCK_DEPTH / DUCK_RECOVER / DUCK_CHANNELS). v1: no UI, no per-project save.
    static void LoadDuckConfig();
    static void TriggerDuck();   // kick hit -> drop ducked channels to the floor
    static void NewAudioBlock(); // call once per audio block before rendering
    static bool DuckEnabled() { return sDuckEnabled_; }
    static int DuckTrigger() { return sDuckTrigger_; }

  private:
	int index_ ;
	I_Instrument *instr_ ;
	bool muted_ ;
    fixed volume_;
    int busIndex_ ;
	MixBus *mixBus_ ;
    fixed hpfPrevInput_[2];
    fixed hpfPrevOutput_[2];
	fixed hpfAlpha_;
	unsigned char hpfMode_;
    fixed lpfPrevOutput_[2];
    fixed lpfAlpha_;
    unsigned short lpfFreq_;

    // Shared sidechain ducker state (one envelope for all channels)
    static bool sDuckEnabled_;
    static int sDuckTrigger_;              // trigger channel index (the kick)
    static unsigned int sDuckMask_;        // bit i set => channel i ducks
    static fixed sDuckFloor_;              // gain at full duck (1 - depth)
    static fixed sDuckRecoverPerSample_;   // gain climbed back per sample
    static fixed sDuckGain_;               // current shared duck gain (1 = none)
    static int sDuckBlockToken_;           // bumped once per audio block
    static int sDuckAppliedToken_;         // block whose ramp was computed
    static fixed sDuckBlockStart_;         // gain at the start of this block
};

#endif
