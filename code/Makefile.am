AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-I "./include" \
	$(OGF_CFLAGS) $(OgreBullet_CFLAGS) $(bullet_CFLAGS) $(jsoncpp_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g
	 -O3

AM_LDFLAGS = -I /usr/local/lib $(OGF_LIBS) $(OgreBullet_LIBS) $(bullet_LIBS) $(jsoncpp_LIBS)

bin_PROGRAMS = CrazyTennis

CrazyTennis_SOURCES = \
	src/main.cpp \
	src/InputAdapter.cpp \
	src/Model.cpp \
	src/SoundPlayer.cpp \
	src/SceneFactory.cpp \
	src/data/Loader.cpp \
	src/data/Match.cpp \
	src/data/Player.cpp \
	src/data/PointStateListener.cpp \
	src/data/PointStateMachine.cpp \
	src/data/RecordsStorage.cpp \
	src/data/Tournament.cpp \
	src/data/TournamentFactory.cpp \
	src/dynamics/ShotSimulator.cpp \
	src/scenes/Match.cpp \
	src/scenes/Splash.cpp \
	src/scenes/menus/Base.cpp \
	src/scenes/menus/Main.cpp \
	src/scenes/menus/Records.cpp \
	src/scenes/menus/SettingsControls.cpp \
	src/scenes/menus/SettingsMain.cpp \
	src/scenes/menus/SelectPlayer.cpp \
	src/widgets/Ball.cpp \
	src/widgets/PhysicalBase.cpp \
	src/widgets/PlayerBase.cpp \
	src/widgets/PlayerCpu.cpp \
	src/widgets/PlayerHuman.cpp \
	src/widgets/PlayerMotion.cpp \
	src/widgets/Score.cpp \
	src/widgets/ServerMark.cpp \
	src/widgets/ShotBuffer.cpp

CrazyTennis_LDFLAGS = $(OGF_LIBS) $(OgreBullet_LIBS) $(bullet_LIBS) $(jsoncpp_LIBS)
CrazyTennis_LDADD = $(OGF_LIBS) $(OgreBullet_LIBS) $(bullet_LIBS) $(jsoncpp_LIBS)
